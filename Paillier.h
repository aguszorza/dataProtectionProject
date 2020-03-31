//
// Created by agustin on 15/3/20.
//

#ifndef PAILLER_PAILLIER_H
#define PAILLER_PAILLIER_H

#include "Mpz.h"

class Paillier {
public:
    Mpz p;
    Mpz q;
    Mpz N;
    Mpz FI;
    Mpz N2;


    Paillier(const Mpz& p, const Mpz& q);

    ~Paillier();

    Mpz encode(const Mpz& message, const Mpz& r) const;

    Mpz encode(const int message, const Mpz& r) const;

    Mpz decode(const Mpz& encoded) const;
};


#endif //PAILLER_PAILLIER_H
