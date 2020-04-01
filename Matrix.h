#ifndef PAILLER_MATRIX_H
#define PAILLER_MATRIX_H

#include <vector>
#include "Mpz.h"

class Matrix {
private:
    std::vector< std::vector<Mpz> > matrix;

public:
    Matrix();

    Matrix(const unsigned int rows, const unsigned int columns, int maxValue);

    ~Matrix();

    std::vector<Mpz> operator[](size_t row) const;

    void printMatrix(int dataWidth);

    size_t size() const;

    void push_back(std::vector<Mpz> row);
};


#endif //PAILLER_MATRIX_H
