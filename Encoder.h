#ifndef PAILLER_ENCODER_H
#define PAILLER_ENCODER_H

#include <string>
#include "Mpz.h"
#include "Matrix.h"

class Encoder {
private:
    std::string tattoo;
    unsigned long int KS;
    int column1;
    int column2;

public:
    Encoder(std::string& tattoo, unsigned long int& KS, int& column1, int& column2);

    ~Encoder();

    Matrix encode(const Mpz& p, const Mpz& q, const Matrix& matrix, int& EP);

    Matrix decode_3_3_1(const Mpz& p, const Mpz& q, const Matrix& matrix, const int& EP);

    Matrix decode_3_3_2(const Mpz& p, const Mpz& q, const Matrix& matrix, const int& EP);
};


#endif //PAILLER_ENCODER_H
