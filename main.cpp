#include <iostream>
#include "Mpz.h"
#include "Generator.h"
#include "Paillier.h"
#include "DataHider.h"

#include <vector>
#include <cstdlib>
#include <ctime>

int MAX_VALUE = 255;

std::vector< std::vector<int> > generate_data(const unsigned int rows, const unsigned int columns) {
    std::srand(std::time(NULL));
    std::vector< std::vector<int> > matrix;
    for (unsigned int i = 0; i < rows; i++) {
        std::vector<int> row;
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
    std::vector< std::vector<int> > matrix = generate_data(5, 5);

    print_matrix(matrix, 5, 5);
}

std::vector< std::vector<int> > generate_test_matrix() {
    // Matrix 3x3
    std::vector< std::vector<int> > matrix;
    int row_1[] = {5, 2, 2}; // d = 3
    int row_2[] = {7, 101, 10}; // d = 3
    int row_3[] = {25, 47, 25}; // d = 3

    std::vector<int> row1(row_1, row_1 + sizeof(row_1) / sizeof(int));
    std::vector<int> row2(row_2, row_2 + sizeof(row_2) / sizeof(int));
    std::vector<int> row3(row_3, row_3 + sizeof(row_3) / sizeof(int));

    matrix.push_back(row1);
    matrix.push_back(row2);
    matrix.push_back(row3);

    return matrix;
}

int main() {
    Generator generator;

    Mpz p = 11;
    Mpz q = 3;
//    Mpz p = generator.generate_prime(512, 24);
//    Mpz q = generator.generate_prime(512, 24);
    Mpz r = generator.generate_prime(10, 24);
    Mpz r2 = generator.generate_prime(10, 24);
    Mpz encoded1, encoded2, encoded3, decoded;

    Paillier paillier(p, q);

    int pixel1 = 5; // TODO: WARNING: d value might be wrong if we use p = 11 and q = 3 (they are small values)
    int pixel2 = 2;

    encoded1 = paillier.encode(pixel1, r);
    encoded2 = paillier.encode(pixel2, r);

    encoded3 = encoded2 * paillier.encode(0, r * r2);
    std::cout << "r = " << r << std::endl;
    std::cout << "r2 = " << r2 << std::endl;


    std::cout << "Pailler(" << pixel1 << ") = " << encoded1 << std::endl;
    std::cout << "Pailler(" << pixel2 << ") = " << encoded2 << std::endl;
    std::cout << "Pailler(" << encoded2 << ") = " << encoded3 << std::endl;

    std::cout << "Decode Pailler = " << paillier.decode(encoded1) << std::endl;
    std::cout << "Decode Pailler = " << paillier.decode(encoded2) << std::endl;
    std::cout << "Decode Pailler = " << paillier.decode(encoded3) << std::endl;

    DataHider dataHider(p, q);
    std::list<Mpz> list = dataHider.get_encrypted_differences(encoded1, encoded2);
    std::cout << "Cd1(con lista) = " << list.front() << std::endl;
    std::cout << "Cd2(con lista) = " << list.back() << std::endl;

    std::cout << "d(con lista) = " << dataHider.get_difference(list.front(), list.back()) << std::endl;

    //test_matrix();

    std::cout << "\n\nTESTEANDO CON MATRIZ\n\n" << std::endl;

    std::vector< std::vector<int> > matrix = generate_test_matrix();
    print_matrix(matrix, 3, 3);

    Generator generator_r1;
    Generator generator_r2(1926492749); // TODO: Choose a better number

    for (int row = 0; row < 3; row++) {
        std::cout << "\n****************************" << std::endl;
        std::cout << "Row " << row + 1 << "" << std::endl;
        std::cout << "****************************\n" << std::endl;

        pixel1 = matrix[row][0];
        pixel2 = matrix[row][2];

        r = generator_r1.generate_prime(10, 24);
        r2 = generator_r2.generate_prime(10, 24);

        encoded1 = paillier.encode(pixel1, r);
        encoded2 = paillier.encode(pixel2, r);

        encoded3 = encoded2 * paillier.encode(0, r * r2);
        std::cout << "r1 = " << r << std::endl;
        std::cout << "r2 = " << r2 << std::endl;


        std::cout << "Pailler(" << pixel1 << ") = " << encoded1 << std::endl;
        std::cout << "Pailler(" << pixel2 << ") = " << encoded2 << std::endl;
        std::cout << "Pailler(" << encoded2 << ") = " << encoded3 << std::endl;

        std::cout << "Decode Pailler = " << paillier.decode(encoded1) << std::endl;
        std::cout << "Decode Pailler = " << paillier.decode(encoded2) << std::endl;
        std::cout << "Decode Pailler = " << paillier.decode(encoded3) << std::endl;

        std::list<Mpz> list2 = dataHider.get_encrypted_differences(encoded1, encoded2);
        std::cout << "Cd1(con lista) = " << list2.front() << std::endl;
        std::cout << "Cd2(con lista) = " << list2.back() << std::endl;

        std::cout << "d(con lista) = " << dataHider.get_difference(list2.front(), list2.back()) << std::endl;
    }
}
