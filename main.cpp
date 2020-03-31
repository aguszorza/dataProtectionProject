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

int find_d(const Mpz& value, const Mpz& g, const Mpz& N2) {
    // TODO: find a better way to solve it.
    int i = -1;
    Mpz aux = -1;
    while (i <= MAX_VALUE && aux != value) {
        i += 1;
        aux = g.powm(Mpz(i), N2);
    }
    return i;
}

void hider(const Mpz& c1, const Mpz& c2, const Mpz& p, const Mpz& q) {
    Mpz out_value1, out_value2;
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz FI = (p - 1) * (q - 1);
    Mpz g = N + 1;


    Mpz cd1, cd2;
    Mpz tetha1 = c1.invert(N2);
    Mpz tetha2 = c2.invert(N2);

    cd1 = (c1 * tetha2).mod(N2);
    cd2 = (c2 * tetha1).mod(N2);

    int d1 = find_d(cd1, g, N2);
    int d2 = find_d(cd2, g, N2);

    if (d1 != 256) {
        std::cout << "P1 >= P2, d = " << d1 << std::endl;
    } else {
        std::cout << "P2 > P1, d = " << d2 << std::endl;
    }

//    if (value1 < value2) {
//        out_value2 = value2 - value1;
//        out_value1 = N * FI - out_value2;
//    } else {
//        out_value1 = value1 - value2;
//        out_value2 = N * FI - out_value1;
//    }
//    out_value1 = g.powm(out_value1, N2);
//    out_value2 = g.powm(out_value2, N2);
//
//    std::cout << "Cd1 = " << out_value1 << std::endl;
//    std::cout << "Cd2 = " << out_value2 << std::endl;
//
//    std::cout << "d1 = " << find_d(out_value1, g, N2) << std::endl;
//    std::cout << "d2 = " << find_d(out_value2, g, N2) << std::endl;


    // TODO: ADD IF
    // d1 = 3, d2 = 30 TODO: add the algorithm to find this
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

    int pixel1 = 5;
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

    std::cout << "***USANDO LOS PIXELES***" << std::endl;
    hider(Mpz(pixel1), Mpz(pixel2), p, q);

    Mpz N2 = p * q * p * q;
    Mpz tetha1 = encoded1.invert(N2);
    Mpz tetha2 = encoded2.invert(N2);
    Mpz cd1 = (encoded1 * tetha2).mod(N2);

    std::cout << "Cd1(con tetha) = " << cd1 << std::endl;
    std::cout << "Cd2(con tetha) = " << (encoded2 * tetha1).mod(N2) << std::endl;
    std::cout << "d(tetha) = " << find_d(cd1, p*q+1, N2) << std::endl;

    std::cout << "***USANDO LOS PIXELES ENCRIPTADOS***" << std::endl;
    hider(encoded1, encoded2, p, q);


    // asdasd
    DataHider dataHider(p, q);
    std::list<Mpz> list = dataHider.get_encrypted_differences(encoded1, encoded2);
    std::cout << "Cd1(con lista) = " << list.front() << std::endl;
    std::cout << "Cd2(con lista) = " << list.back() << std::endl;

    std::cout << "d(con lista) = " << dataHider.get_difference(list.front(), list.back()) << std::endl;

    test_matrix();
}
