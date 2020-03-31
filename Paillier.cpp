#include "Paillier.h"

Paillier::Paillier(const Mpz& p, const Mpz& q) {
    this->p = p;
    this->q = q;
    this->N = p * q;
    this->N2 = this->N * this->N;
    this->FI = (p - 1) * (q - 1);
}

Paillier::~Paillier() {}

Mpz Paillier::encode(const Mpz& message, const Mpz& r) const {
    Mpz encoded;

    encoded = this->N + 1;
    encoded = encoded.powm(message, this->N2);
    encoded *= r.powm(this->N, this->N2);
    return encoded.mod(this->N2);
}

Mpz Paillier::encode(const int message, const Mpz& r) const {
    Mpz m(message);
    return this->encode(m, r);
}

Mpz Paillier::decode(const Mpz& encoded) const {
    Mpz decoded, aux;

    decoded = encoded.powm(this->FI, this->N2);
    decoded -= 1;
    decoded /= N;

    aux = this->FI.invert(N);
    decoded *= aux;
    return decoded.mod(N);
}

