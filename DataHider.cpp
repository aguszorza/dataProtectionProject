#include "DataHider.h"

DataHider::DataHider(const Mpz& p, const Mpz& q) {
    this->p = p;
    this->q = q;
    this->N = p * q;
    this->N2 = this->N * this->N;
    this->g = this->N + 1;
    this->FI = (p - 1) * (q - 1);
    this->MAX_VALUE = 256;
}

DataHider::~DataHider() {}

std::list<Mpz> DataHider::get_encrypted_differences(const Mpz& c1, const Mpz& c2) const{
    Mpz cd1, cd2;
    std::list<Mpz> result;

    Mpz theta1 = c1.invert(this->N2);
    Mpz theta2 = c2.invert(this->N2);

    cd1 = (c1 * theta2).mod(this->N2);
    cd2 = (c2 * theta1).mod(this->N2);

    result.push_back(cd1);
    result.push_back(cd2);

    return result;
}

int DataHider::find_d(const Mpz& cd) const {
    int d = -1;
    Mpz aux = -1;
    while (d < this->MAX_VALUE && aux != cd) {
        d += 1;
        aux = g.powm(Mpz(d), this->N2);
    }
    return d;
}

Difference DataHider::get_difference(const Mpz& cd1, const Mpz& cd2) const {
    int d1 = this->find_d(cd1);
    int d2 = this->find_d(cd2);
    if (d1 < this->MAX_VALUE) {
        return Difference(d1, 1);
    }
    return Difference(d2, -1);
}
