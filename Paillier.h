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

    /* It encodes the message using Paillier */
    Mpz encode(const Mpz& message, const Mpz& r) const;

    /* It encodes the message using Paillier */
    Mpz encode(const int message, const Mpz& r) const;

    /* It decodes the message using Paillier */
    Mpz decode(const Mpz& encoded) const;
};


#endif //PAILLER_PAILLIER_H
