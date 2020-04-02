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

    /* It generates a matrix with that amount of rows and columns. The values are
     * generate randomly with a maximum value restriction*/
    Matrix(const unsigned int rows, const unsigned int columns, int maxValue);

    /* It generates a matrix from a vector of vectors */
    Matrix(const std::vector< std::vector<Mpz> >& matrix);

    /* It generates a matrix from the content of a csv file */
    Matrix(const std::string& filename);

    ~Matrix();

    /* It returns the row in that position */
    std::vector<Mpz> operator[](size_t row) const;

    /* It returns the row in that position */
    std::vector<Mpz>& operator[](size_t row);

    /* It prints the matrix */
    void printMatrix(int dataWidth) const;

    /* It returns the amounts of rows of the matrix */
    size_t size() const;

    /* it adds a row to the matrix */
    void push_back(std::vector<Mpz> row);

    /* It saves the matrix in the file with a csv format */
    void saveAsCsv(std::ofstream& file) const;

    /* It saves the matrix in the file with a txt format */
    void saveAsText(std::ostream& file, int dataWidth) const;
};


#endif //PAILLER_MATRIX_H
