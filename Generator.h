#ifndef PAILLER_GENERATOR_H
#define PAILLER_GENERATOR_H

#include <gmp.h>
#include "Mpz.h"

class Generator {
private:
    gmp_randstate_t generator;

public:
    Generator();

    ~Generator();

    Mpz urandomb(int value);

    /* It generates a random prime value with size bits
     * It verifies repetitions times */
    Mpz generate_prime(size_t size, int repetitions);
};


#endif //PAILLER_GENERATOR_H
