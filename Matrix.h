#ifndef PAILLER_MATRIX_H
#define PAILLER_MATRIX_H

#include <vector>
#include <fstream>
#include "Mpz.h"

class Matrix {
private:
    std::vector< std::vector<Mpz> > matrix;

public:
    Matrix();

    Matrix(const unsigned int rows, const unsigned int columns, int maxValue);

    Matrix(const std::vector< std::vector<Mpz> >& matrix);

    Matrix(const std::string& filename);

    ~Matrix();

    std::vector<Mpz> operator[](size_t row) const;

    std::vector<Mpz>& operator[](size_t row);

    void printMatrix(int dataWidth) const;

    size_t size() const;

    void push_back(std::vector<Mpz> row);

    void saveAsCsv(std::ofstream& file) const;

    void saveAsText(std::ostream& file, int dataWidth) const;
};


#endif //PAILLER_MATRIX_H
