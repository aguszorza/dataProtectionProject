#include <iostream>
#include "Mpz.h"
#include "Generator.h"
#include "Matrix.h"
#include "Utils.h"
#include "Parser.h"
#include "Encoder.h"

#include <string>

int MAX_VALUE = 256;
int MATRIX_WIDTH = 3;

// Default values
unsigned long int KS = 637353949689553;
std::string TATTOO("10101000111010101");
int COLUMN_1 = 0;
int COLUMN_2 = 2;
int COLUMNS = 3;
int ROWS = 6;
std::string MATRIX_FILE = "";

int main(int argc, char *argv[]) {
    if (argc % 2 == 0) {
        std::cout << "Parameter input error" << std::endl;
        return 1;
    }
    // We get the values
    try {
        Parser parser(argc, argv);
        TATTOO = parser.getTattoo(TATTOO);
        COLUMNS = parser.getColumns(COLUMNS);
        ROWS = parser.getRows(ROWS);
        COLUMN_1 = parser.getColumn1(COLUMN_1);
        COLUMN_2 = parser.getColumn2(COLUMN_2);
        KS = parser.getKs(KS);
        MATRIX_FILE = parser.getFilename(MATRIX_FILE);
        if (COLUMN_1 == COLUMN_2) {
            throw std::runtime_error("Invalid value Column 1 and 2: they should have a different value");
        }
    } catch (std::runtime_error& error)  {
        std::cout << error.what() << std::endl;
        return 1;
    }

    // We initialize the variables we are going to use
    Generator generator;
    Matrix original_matrix, encoded_matrix, decoded_matrix;
    int EP;

    Mpz p = generator.generate_prime(512, 24);
    Mpz q = generator.generate_prime(512, 24);
    Encoder encoder(TATTOO, KS, COLUMN_1, COLUMN_2);

    // We create a matrix with random data

    if (MATRIX_FILE.empty()) {
        original_matrix = Matrix(ROWS, COLUMNS, MAX_VALUE);
    } else {
        original_matrix = Matrix(MATRIX_FILE);
    }

    // We save the original matrix in two formats
    Utils::saveMatrixInTxt("./output/original", original_matrix, MATRIX_WIDTH);
    Utils::saveMatrixInCsv("./output/original", original_matrix);

    Utils::printTitle("Original Matrix");
    original_matrix.printMatrix(MATRIX_WIDTH);

    // We encode the matrix
    encoded_matrix = encoder.encode(p, q, original_matrix, EP);//encode(p, q, original_matrix, EP);

    std::cout << "EP = " << EP << std::endl;

    // We decode the encoded matrix using the approach 3.3.1 from the paper
    Utils::printTitle("Starting decode (approach 3.3.1)");
    decoded_matrix = encoder.decode_3_3_1(p, q, encoded_matrix, EP); //decode_3_3_1(p, q, encoded_matrix, EP);
    decoded_matrix.printMatrix(MATRIX_WIDTH);

    Utils::saveMatrixInTxt("./output/decoded_3_3_1", decoded_matrix, MATRIX_WIDTH);
    Utils::saveMatrixInCsv("./output/decoded_3_3_1", decoded_matrix);

    // We decode the encoded matrix using the approach 3.3.2 from the paper
    Utils::printTitle("Starting decode (approach 3.3.2)");
    decoded_matrix = encoder.decode_3_3_2(p, q, encoded_matrix, EP);//decode_3_3_2(p, q, encoded_matrix, EP);
    decoded_matrix.printMatrix(MATRIX_WIDTH);

    Utils::saveMatrixInTxt("./output/decoded_3_3_2", decoded_matrix, MATRIX_WIDTH);
    Utils::saveMatrixInCsv("./output/decoded_3_3_2", decoded_matrix);

    return 0;
}
