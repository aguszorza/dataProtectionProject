#include "Matrix.h"
#include <ctime>
#include <cstdlib>


Matrix::Matrix() {}

Matrix::Matrix(const unsigned int rows, const unsigned int columns, int maxValue) {
    std::srand(std::time(NULL));
    for (unsigned int i = 0; i < rows; i++) {
        std::vector<Mpz> row;
        for (unsigned int j = 0; j < columns; j++){
            row.push_back(std::rand() % (maxValue));
        }
        this->matrix.push_back(row);
    }
}

Matrix::Matrix(const std::vector< std::vector<Mpz> >& matrix) {
    this->matrix = matrix;
}

Matrix::~Matrix() {}

std::vector<Mpz> Matrix::operator[](size_t row) const {
    std::vector<Mpz> result = this->matrix[row];
    return result;
}

std::vector<Mpz>& Matrix::operator[](size_t row) {
    return this->matrix[row];
}

void Matrix::printMatrix(int dataWidth) {
    for (unsigned int row = 0; row < this->matrix.size(); row++) {
        std::cout << "| ";
        for (unsigned int column = 0; column < this->matrix[row].size(); column++){
            std::cout.width(dataWidth);
            std::cout << this->matrix[row][column] << " ";
        }
        std::cout << "|" << std::endl;
    }
}

size_t Matrix::size() const {
    return this->matrix.size();
}

void Matrix::push_back(std::vector<Mpz> row) {
    this->matrix.push_back(row);
}
