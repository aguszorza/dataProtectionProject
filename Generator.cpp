#include "Generator.h"
#include <time.h>

Generator::Generator() {
    gmp_randinit_default(this->generator);
    gmp_randseed_ui(this->generator, time(NULL));
}

Generator::~Generator() {
    gmp_randclear(this->generator);
}

Mpz Generator::urandomb(int value) {
    Mpz result;
    mpz_urandomb(result.gmp, this->generator, value);
    return result;
}

Mpz Generator::generate_prime(size_t size, int repetitions) {
    Mpz result;
    int is_prime = 0;
    size_t actual_size = 0;
    int base = 2;
    while (is_prime < 1 || actual_size != size) {
        mpz_urandomb(result.gmp, generator, size);
        is_prime = mpz_probab_prime_p(result.gmp, repetitions);
        actual_size = mpz_sizeinbase(result.gmp, base);
    }
    return result;
}
