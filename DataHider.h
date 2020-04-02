#ifndef PAILLER_DATAHIDER_H
#define PAILLER_DATAHIDER_H


#include "Mpz.h"
#include "Difference.h"
#include <list>

class DataHider {
private:
    Mpz N, N2, FI, g, p, q;
    int MAX_VALUE;

    int find_d(const Mpz& cd1) const;

public:
    DataHider(const Mpz& p, const Mpz& q);

    ~DataHider();

    /* It calculates the difference between the two encrypted values */
    std::list<Mpz> get_encrypted_differences(const Mpz& c1, const Mpz& c2) const;

    /* It calculates the difference between the two real values using the encrypted values */
    Difference get_difference(const Mpz& cd1, const Mpz& cd2) const;
};


#endif //PAILLER_DATAHIDER_H
