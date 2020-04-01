#include <iostream>
#include "Mpz.h"
#include "Generator.h"
#include "Paillier.h"
#include "DataHider.h"
#include "Histogram.h"
#include "Matrix.h"
#include "Utils.h"
#include "TattooAggregator.h"
#include "Parser.h"


#include <vector>
#include <string>

int MAX_VALUE = 256;
unsigned long int KS = 1926492749; // TODO: Choose a better number
std::string TATTOO("10101000111010101");
std::string EMPTY_TATTOO = "";
int COLUMN_1 = 0;
int COLUMN_2 = 2;
int COLUMNS = 3;
int ROWS = 6;
std::string MATRIX_FILE = "";

void printTitle(const std::string& title) {
    std::cout << "\n**********************************" << std::endl;
    std::cout << title << std::endl;
    std::cout << "**********************************\n" << std::endl;
}

void saveMatrixInCsv(const std::string& filename, const Matrix& matrix) {
    std::ofstream csvFile ((filename + ".csv").c_str());
    matrix.saveAsCsv(csvFile);
    csvFile.close();
}

void saveMatrixInTxt(const std::string& filename, const Matrix& matrix) {
    std::ofstream txtFile ((filename + ".txt").c_str());
    matrix.saveAsText(txtFile, 3);
    txtFile.close();
}

Matrix encode(const Mpz& p, const Mpz& q, const Matrix& matrix, int& EP) {
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz g = N + 1;
    TattooAggregator tattooAggregator(g, N2, TATTOO);
    Paillier paillier(p, q);
    DataHider dataHider(p, q);

    Generator generator_r1;
    Generator generator_r2(KS);

    std::vector<Difference> d_list;
    Histogram histogram;

    Matrix c_matrix, cd_matrix, final_matrix;

    printTitle("Starting encoding");

    c_matrix = Utils::paillierEncodeMatrix(matrix, paillier, generator_r1, COLUMN_1, COLUMN_2);
    cd_matrix = Utils::getEncryptedDifferences(c_matrix, dataHider, COLUMN_1, COLUMN_2);
    d_list = Utils::getDifferences(cd_matrix, dataHider, COLUMN_1, COLUMN_2);

    histogram = Utils::generateHistogram(d_list, dataHider, COLUMN_1, COLUMN_2);

    EP = histogram.get_max_key();
    final_matrix = Utils::addTattoo(c_matrix, d_list, tattooAggregator, EP, COLUMN_1, COLUMN_2);
    std::cout << "Added tattoo = " << tattooAggregator.getAddedTattoo() << std::endl;
    final_matrix = Utils::paillierVoidEncrypting(final_matrix, paillier, generator_r2, COLUMN_1, COLUMN_2);

    saveMatrixInCsv("./output/encoded_paillier", c_matrix);
    saveMatrixInCsv("./output/encoded_differences", cd_matrix);
    saveMatrixInCsv("./output/encoded_with_tattoo", final_matrix);

    return final_matrix;
}

Matrix decode_3_3_1(const Mpz& p, const Mpz& q, const Matrix& matrix, const int& EP) {
    Generator generator_r2(KS);
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz g = N + 1;

    TattooAggregator tattooAggregator(g, N2, EMPTY_TATTOO); // TODO: w is not necessary
    Paillier paillier(p, q);
    DataHider dataHider(p, q);

    std::vector<Difference> d_list;
    Matrix c_matrix, cw_matrix, cdw_matrix, decoded_matrix;

    cw_matrix = Utils::paillierRemoveVoidEncrypting(matrix, paillier, generator_r2, COLUMN_1, COLUMN_2);
    cdw_matrix = Utils::getEncryptedDifferences(cw_matrix, dataHider, COLUMN_1, COLUMN_2);
    d_list = Utils::getDifferences(cdw_matrix, dataHider, COLUMN_1, COLUMN_2);

    std::cout << "Added tattoo = " << Utils::getTattoo(d_list, tattooAggregator, EP) << std::endl;
    // we get c1 and c2
    c_matrix = Utils::removeTattoo(cw_matrix, d_list, tattooAggregator, EP, COLUMN_1, COLUMN_2);

    decoded_matrix = Utils::paillierDecodeMatrix(c_matrix, paillier, COLUMN_1, COLUMN_2);

    return decoded_matrix;
}

Matrix decode_3_3_2(const Mpz& p, const Mpz& q, const Matrix& matrix, const int& EP) {
    Generator generator_r2(KS);
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz g = N + 1;

    TattooAggregator tattooAggregator(g, N2, EMPTY_TATTOO);
    Paillier paillier(p, q);
    DataHider dataHider(p, q);

    std::vector<Difference> d_list;
    Matrix pw_matrix, cw_matrix, cdw_matrix, decoded_matrix;

    cw_matrix = Utils::paillierRemoveVoidEncrypting(matrix, paillier, generator_r2, COLUMN_1, COLUMN_2);
    pw_matrix = Utils::paillierDecodeMatrix(cw_matrix, paillier, COLUMN_1, COLUMN_2);

    d_list = Utils::getDecodedDifferences(pw_matrix, COLUMN_1, COLUMN_2);
    std::cout << "Added tattoo = " << Utils::getTattoo(d_list, tattooAggregator, EP) << std::endl;

    decoded_matrix = Utils::removeAdditionalData(pw_matrix, d_list, tattooAggregator, EP, COLUMN_1, COLUMN_2);

    return decoded_matrix;
}

int main(int argc, char *argv[]) {
    if (argc % 2 == 0) {
        std::cout << "Parameter input error" << std::endl;
        return 1;
    }
    // We get the values
    Parser parser(argc, argv);
    TATTOO = parser.getTattoo(TATTOO);
    COLUMNS = parser.getColumns(COLUMNS);
    ROWS = parser.getRows(ROWS);
    COLUMN_1 = parser.getColumn1(COLUMN_1);
    COLUMN_2 = parser.getColumn2(COLUMN_2);
    KS = parser.getKs(KS);
    MATRIX_FILE = parser.getFilename(MATRIX_FILE);

    // We initialize the variables we are going to use
    Generator generator;
    Matrix encoded_matrix, decoded_matrix;
    int EP;

    Mpz p = generator.generate_prime(512, 24);
    Mpz q = generator.generate_prime(512, 24);

    printTitle("Original Matrix");

    // We create a matrix with random data
    Matrix original_matrix;
    if (MATRIX_FILE.empty()) {
        original_matrix = Matrix(ROWS, COLUMNS, MAX_VALUE);
    } else {
        original_matrix = Matrix(MATRIX_FILE);
    }
    saveMatrixInTxt("./output/original", original_matrix);
    saveMatrixInCsv("./output/original", original_matrix);

//    original_matrix[0][0] = 100;
//    original_matrix[0][2] = 130;
//    original_matrix[1][0] = 73;
//    original_matrix[1][2] = 103;

    original_matrix.printMatrix(3);

    // We encode the matrix
    encoded_matrix = encode(p, q, original_matrix, EP);

    std::cout << "EP = " << EP << std::endl;

    printTitle("Starting decode (approach 3.3.1)");
    // We decode the encoded matrix using the approach 3.3.1 from the paper
    decoded_matrix = decode_3_3_1(p, q, encoded_matrix, EP);
    decoded_matrix.printMatrix(3);

    saveMatrixInTxt("./output/decoded_3_3_1", decoded_matrix);
    saveMatrixInCsv("./output/decoded_3_3_1", decoded_matrix);

    printTitle("Starting decode (approach 3.3.2)");
    // We decode the encoded matrix using the approach 3.3.2 from the paper
    decoded_matrix = decode_3_3_2(p, q, encoded_matrix, EP);
    decoded_matrix.printMatrix(3);
    saveMatrixInTxt("./output/decoded_3_3_2", decoded_matrix);
    saveMatrixInCsv("./output/decoded_3_3_2", decoded_matrix);

    return 0;
}
