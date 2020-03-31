#include <iostream>
#include "Mpz.h"
#include "Generator.h"
#include "Paillier.h"
#include "DataHider.h"

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>

int MAX_VALUE = 255;
unsigned long int KS = 1926492749; // TODO: Choose a better number
std::string W = "00101000111010101";

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

int get_max_histogram(std::map<int,int> histogram) {
    int max_value = -1;
    int max_d = -1;
    for (std::map<int,int>::iterator it = histogram.begin(); it != histogram.end(); it++) {
        if (it->second > max_value) {
            max_d = it->first;
            max_value = it->second;
        }
    }
    std::cout << "quantity = " << histogram[max_d] << std::endl;
    return max_d;
}

std::vector<Mpz> get_cdw(const Mpz& c1, const Mpz& c2, int d, int max_d_value, int w, const Mpz& g, int& w_pos) {
    std::vector<Mpz> result;
    if (d < max_d_value) {
        result.push_back(c1);
    } else if (d == max_d_value) {
        result.push_back(c1 * g.pow(w));
        std::cout << "Caso =, w = " << w << " cdw = " << result.back() << std::endl;
        w_pos += 1;
    } else {
        result.push_back(c1 * g);
    }
    result.push_back(c2);
    return result;
}

void decode(const std::vector< std::vector<Mpz> >& matrix, const Paillier& paillier) {
    Generator generator_r2(KS);
    Mpz r2;
    Mpz theta_er, theta_1, theta_2, theta_g;
    std::vector<int> d_list;
    std::vector< std::vector<Mpz> > encoded_matrix;
    std::vector< std::vector<Mpz> > cdw_matrix;
    std::map<int,int> histogram;
    DataHider dataHider(paillier.p, paillier.q);
    for (int row = 0; row < 6; row++) {
        encoded_matrix.push_back(matrix[row]);
        r2 = generator_r2.generate_prime(10, 24);
        theta_er = paillier.encode(0, r2).invert(paillier.N2);
        encoded_matrix[row][2] = (encoded_matrix[row][2] * theta_er).mod(paillier.N2);
        cdw_matrix.push_back(encoded_matrix[row]);

        theta_1 = encoded_matrix[row][0].invert(paillier.N2);
        theta_2 = encoded_matrix[row][2].invert(paillier.N2);

        // eq 34
        cdw_matrix[row][0] = (encoded_matrix[row][0] * theta_2).mod(paillier.N2);
        cdw_matrix[row][2] = (encoded_matrix[row][2] * theta_1).mod(paillier.N2);

        // histogram
        int d = dataHider.get_difference(cdw_matrix[row][0], cdw_matrix[row][2]);

        d_list.push_back(d);

        if (histogram.find(d) == histogram.end()) {
            histogram.insert(std::pair<int,int>(d, 0));
        }
        histogram[d] += 1;

    }
    theta_g = (paillier.N + 1).invert(paillier.N2);
    int max_d = 4;//get_max_histogram(histogram);
    std::cout << "max d = " << max_d << std::endl;
    int cmp;
    // we get c1 and c2
    for (int row = 0; row < 6; row++) {
        cmp = dataHider.compare(cdw_matrix[row][0], cdw_matrix[row][2]);
        if (cmp > 0) {
            if (d_list[row] > max_d) {
                encoded_matrix[row][0] = (encoded_matrix[row][0] * theta_g).mod(paillier.N2);
            }
        } else {
            if (d_list[row] > max_d) {
                encoded_matrix[row][2] = (encoded_matrix[row][2] * theta_g).mod(paillier.N2);
            }
        }
    }
    // we decode with pailler (we obtain P1w and P2w)
    for (int row = 0; row < 6; row++) {
        encoded_matrix[row][0] = paillier.decode(encoded_matrix[row][0]);
        encoded_matrix[row][2] = paillier.decode(encoded_matrix[row][2]);
    }

    std::cout << "\nBefore substracting 1\n" << std::endl;
    print_matrix(encoded_matrix, 6, 3);

    for (int row = 0; row < 6; row++) {
        cmp = dataHider.compare(cdw_matrix[row][0], cdw_matrix[row][2]);
        std::cout << "CMP row " << row << " = " << cmp << std::endl;
        if (d_list[row] == max_d){
            std::cout << "w agregada = 0" << std::endl;
        }
        if (d_list[row] == max_d + 1){
            std::cout << "w agregada = 1" << std::endl;
        }
        if (cmp > 0) {
            if (d_list[row] > max_d) {
                encoded_matrix[row][0] = encoded_matrix[row][0] - 1;
            }
        } else {
            if (d_list[row] > max_d) {
                encoded_matrix[row][2] = encoded_matrix[row][2] - 1;
            }
        }
    }
    print_matrix(encoded_matrix, 6, 3);
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

    Paillier paillier(p, q);

    Mpz pixel1 = 5; // TODO: WARNING: d value might be wrong if we use p = 11 and q = 3 (they are small values)
    Mpz pixel2 = 2;

    encoded1 = paillier.encode(pixel1, r);
    encoded2 = paillier.encode(pixel2, r);

    //encoded3 = encoded2 * paillier.encode(0, r2);
    std::cout << "r = " << r << std::endl;
    std::cout << "r2 = " << r2 << std::endl;


    std::cout << "Pailler(" << pixel1 << ") = " << encoded1 << std::endl;
    std::cout << "Pailler(" << pixel2 << ") = " << encoded2 << std::endl;
    //std::cout << "Pailler(" << encoded2 << ") = " << encoded3 << std::endl;

    std::cout << "Decode Pailler = " << paillier.decode(encoded1) << std::endl;
    std::cout << "Decode Pailler = " << paillier.decode(encoded2) << std::endl;
   // std::cout << "Decode Pailler = " << paillier.decode(encoded3) << std::endl;

    DataHider dataHider(p, q);
    std::list<Mpz> list = dataHider.get_encrypted_differences(encoded1, encoded2);
    std::cout << "Cd1(con lista) = " << list.front() << std::endl;
    std::cout << "Cd2(con lista) = " << list.back() << std::endl;

    std::cout << "d(con lista) = " << dataHider.get_difference(list.front(), list.back()) << std::endl;

    //test_matrix();

    std::cout << "\n\nTESTEANDO CON MATRIZ\n\n" << std::endl;

    std::vector< std::vector<Mpz> > original_matrix = generate_test_matrix();
    std::vector< std::vector<Mpz> > c_matrix;
    std::vector< std::vector<Mpz> > cd_matrix;
    std::vector< std::vector<Mpz> > final_matrix;
    print_matrix(original_matrix, 6, 3);

    Generator generator_r1;
    Generator generator_r2(KS);

    std::vector<int> d_list;
    std::map<int,int> histogram;

    for (int row = 0; row < 6; row++) {
        std::cout << "\n****************************" << std::endl;
        std::cout << "Row " << row + 1 << "" << std::endl;
        std::cout << "****************************\n" << std::endl;

        pixel1 = original_matrix[row][0];
        pixel2 = original_matrix[row][2];

        c_matrix.push_back(original_matrix[row]);
        cd_matrix.push_back(original_matrix[row]);
        final_matrix.push_back(original_matrix[row]);

        r = generator_r1.generate_prime(10, 24);

        encoded1 = paillier.encode(pixel1, r);
        encoded2 = paillier.encode(pixel2, r);

        c_matrix[row][0] = encoded1;
        c_matrix[row][2] = encoded2;

       //encoded3 = encoded2 * paillier.encode(0, r2);
        std::cout << "r1 = " << r << std::endl;
        std::cout << "r2 = " << r2 << std::endl;


        std::cout << "Pailler(" << pixel1 << ") = " << encoded1 << std::endl;
        std::cout << "Pailler(" << pixel2 << ") = " << encoded2 << std::endl;
        //std::cout << "Pailler(" << encoded2 << ") = " << encoded3 << std::endl;

        std::cout << "Decode Pailler = " << paillier.decode(encoded1) << std::endl;
        std::cout << "Decode Pailler = " << paillier.decode(encoded2) << std::endl;
        //std::cout << "Decode Pailler = " << paillier.decode(encoded3) << std::endl;

        std::list<Mpz> list2 = dataHider.get_encrypted_differences(encoded1, encoded2);
        std::cout << "Cd1(con lista) = " << list2.front() << std::endl;
        std::cout << "Cd2(con lista) = " << list2.back() << std::endl;

        cd_matrix[row][0] = list2.front();
        cd_matrix[row][2] = list2.back();

        int d = dataHider.get_difference(list2.front(), list2.back());
        std::cout << "d(con lista) = " << d << std::endl;

        d_list.push_back(d);

        if (histogram.find(d) == histogram.end()) {
            histogram.insert(std::pair<int,int>(d, 0));
        }
        histogram[d] += 1;
    }
    int max_d_value = get_max_histogram(histogram);
    std::cout << "\n\nMax value = " << max_d_value << std::endl;
    std::cout << "\n\nStarting histogram part\n\n" << std::endl;
    Mpz cdw1, cdw2;

    int w_pos = 0;
    for (int row = 0; row < 6; row++) {
        int acutal_d = d_list[row];
        int cmp = dataHider.compare(cd_matrix[row][0], cd_matrix[row][2]);
        std::vector<Mpz> result;
        char w_ = W[w_pos] - '0';
        if (cmp > 0) {
            result = get_cdw(c_matrix[row][0], c_matrix[row][2], acutal_d, max_d_value, w_, g, w_pos);
            cdw1 = result.front();
            cdw2 = result.back();
        } else {
            result = get_cdw(c_matrix[row][2], c_matrix[row][0], acutal_d, max_d_value, w_, g, w_pos);
            cdw2 = result.front();
            cdw1 = result.back();
        }

        std::cout << "w = " << W[w_pos] << std::endl;
        //w_pos += 1; // TODO: add one only if it was EP
        std::cout << "Cdw1 = " << cdw1 << std::endl;
        std::cout << "Cdw2 = " << cdw2 << std::endl;

        r2 = generator_r2.generate_prime(10, 24);

        std::cout << "Cdw2' = " << (cdw2 * paillier.encode(0, r2)).mod(N2) << std::endl;

        final_matrix[row][0] = cdw1;
        final_matrix[row][2] = (cdw2 * paillier.encode(0, r2)).mod(N2);
    }
    print_matrix(original_matrix, 6, 3);
    std::cout << "\nStarting Decode\n" << std::endl;
    decode(final_matrix, paillier);
}
