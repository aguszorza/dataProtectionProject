#include <iostream>
#include "Mpz.h"
#include "Generator.h"
#include "Paillier.h"
#include "DataHider.h"
#include "Histogram.h"
#include "Utils.h"
#include "TattooAggregator.h"


#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

int MAX_VALUE = 255;
unsigned long int KS = 1926492749; // TODO: Choose a better number
std::string W = "00101000111010101";

std::vector< std::vector<Mpz> > generate_data(const unsigned int rows, const unsigned int columns) {
    std::srand(std::time(NULL));
    std::vector< std::vector<Mpz> > matrix;
    for (unsigned int i = 0; i < rows; i++) {
        std::vector<Mpz> row;
        for (unsigned int j = 0; j < columns; j++){
            row.push_back(std::rand() % (MAX_VALUE + 1));
        }
        matrix.push_back(row);
    }
    return matrix;
}

template <class T>
void print_matrix(std::vector< std::vector<T> > matrix, const unsigned int rows, const unsigned int columns) {
    for (unsigned int i = 0; i < rows; i++) {
        std::cout << "| ";
        for (unsigned int j = 0; j < columns; j++){
            std::cout.width(5);
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
}

void test_matrix() {
    std::vector< std::vector<Mpz> > matrix = generate_data(5, 5);

    print_matrix(matrix, 5, 5);
}

std::vector< std::vector<Mpz> > generate_test_matrix() {
    // Matrix 3x3
    std::vector< std::vector<Mpz> > matrix;
    Mpz row_1[] = {5, 2, 2}; // d = 3
    Mpz row_2[] = {7, 101, 11}; // d =
    Mpz row_3[] = {25, 47, 25}; // d = 3
    Mpz row_4[] = {25, 47, 99}; // d = 3
    Mpz row_5[] = {255, 47, 250}; // d = 3
    Mpz row_6[] = {125, 47, 129}; // d = 3

    std::vector<Mpz> row1(row_1, row_1 + sizeof(row_1) / sizeof(Mpz));
    std::vector<Mpz> row2(row_2, row_2 + sizeof(row_2) / sizeof(Mpz));
    std::vector<Mpz> row3(row_3, row_3 + sizeof(row_3) / sizeof(Mpz));
    std::vector<Mpz> row4(row_4, row_4 + sizeof(row_4) / sizeof(Mpz));
    std::vector<Mpz> row5(row_5, row_5 + sizeof(row_5) / sizeof(Mpz));
    std::vector<Mpz> row6(row_6, row_6 + sizeof(row_6) / sizeof(Mpz));

    matrix.push_back(row1);
    matrix.push_back(row2);
    matrix.push_back(row3);
    matrix.push_back(row4);
    matrix.push_back(row5);
    matrix.push_back(row6);

    return matrix;
}

std::vector<Mpz> get_cdw(const Mpz& c1, const Mpz& c2, int d, int EP, int w, const Mpz& g, int& w_pos) {
    std::vector<Mpz> result;
    if (d < EP) {
        result.push_back(c1);
    } else if (d == EP) {
        result.push_back(c1 * g.pow(w));
        std::cout << "Caso =, w = " << w << " cdw = " << result.back() << std::endl;
        w_pos += 1;
    } else {
        result.push_back(c1 * g);
    }
    result.push_back(c2);
    return result;
}

void decode(const std::vector< std::vector<Mpz> >& matrix, const Paillier& paillier, const int& EP) {
    Generator generator_r2(KS);
    Mpz r2;
    std::vector<Difference> d_list;
    std::vector< std::vector<Mpz> > cw_matrix, c_matrix, cdw_matrix, encoded_matrix2, decoded_matrix;
    Histogram histogram;
    DataHider dataHider(paillier.p, paillier.q);
    Mpz g = paillier.p * paillier.q + 1; // TODO: get it in another way
    Mpz N2 = paillier.p * paillier.q *  paillier.p * paillier.q; // TODO: get it in another way
    TattooAggregator tattooAggregator(g, N2, W); // TODO: w is not necessary

    cw_matrix = Utils::paillierRemoveVoidEncrypting(matrix, paillier, generator_r2, 0, 2);
    encoded_matrix2 = cw_matrix;
    cdw_matrix = Utils::getEncryptedDifferences(cw_matrix, dataHider, 0, 2);
    d_list = Utils::getDifferences(cdw_matrix, dataHider, 0, 2);


    std::cout << "max d = " << EP << std::endl;
    // we get c1 and c2
    c_matrix = Utils::removeTattoo(cw_matrix, d_list, tattooAggregator, EP, 0, 2);

    decoded_matrix = Utils::paillierDecodeMatrix(c_matrix, paillier, 0, 2);

    std::cout << "DECODIFICANDO DIRECTAMENTE" << std::endl;
    print_matrix(decoded_matrix, 6, 3);
}

int main() {
    Generator generator;

//    Mpz p = 11;
//    Mpz q = 3;
    Mpz p = generator.generate_prime(512, 24);
    Mpz q = generator.generate_prime(512, 24);
    Mpz r = generator.generate_prime(10, 24);
    Mpz r2= generator.generate_prime(10, 24);
    Mpz N2 = p * p * q * q;
    Mpz encoded1, encoded2, decoded; //,encoded3


    Mpz g = p * q + 1;

    TattooAggregator tattooAggregator(g, N2, W);

    Paillier paillier(p, q);

    Mpz pixel1; // TODO: WARNING: d value might be wrong if we use p = 11 and q = 3 (they are small values)
    Mpz pixel2;

    DataHider dataHider(p, q);
    //test_matrix();

    std::cout << "\n\nTESTEANDO CON MATRIZ\n\n" << std::endl;

    std::vector< std::vector<Mpz> > original_matrix = generate_data(6,3);//generate_test_matrix();
    std::vector< std::vector<Mpz> > c_matrix;
    std::vector< std::vector<Mpz> > cd_matrix;
    std::vector< std::vector<Mpz> > final_matrix;
    print_matrix(original_matrix, 6, 3);

    Generator generator_r1;
    Generator generator_r2(KS);

    std::vector<Difference> d_list;
    Histogram histogram;

    c_matrix = Utils::paillierEncodeMatrix(original_matrix, paillier, generator_r1, 0, 2);
    cd_matrix = Utils::getEncryptedDifferences(c_matrix, dataHider, 0, 2);
    d_list = Utils::getDifferences(cd_matrix, dataHider, 0, 2);
    histogram = Utils::generateHistogram(d_list, dataHider, 0, 2);

    int EP = histogram.get_max_key();
    std::cout << "\n\nMax value = " << EP << std::endl;
    std::cout << "\n\nStarting histogram part\n\n" << std::endl;
    final_matrix = Utils::addTattoo(c_matrix, d_list, tattooAggregator, EP, 0, 2);
    final_matrix = Utils::paillierVoidEncrypting(final_matrix, paillier, generator_r2, 0 , 2);

    print_matrix(original_matrix, 6, 3);
    std::cout << "\nStarting Decode\n" << std::endl;
    decode(final_matrix, paillier, EP);
}
