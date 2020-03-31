#ifndef PAILLER_DATAHIDER_H
#define PAILLER_DATAHIDER_H


#include "Mpz.h"
#include <list>

class DataHider {
private:
    Mpz N, N2, FI, g, p, q;
    int MAX_VALUE;

    int find_d(const Mpz& cd1);

public:
    DataHider(const Mpz& p, const Mpz& q);

    ~DataHider();

    std::list<Mpz> get_encrypted_differences(const Mpz& c1, const Mpz& c2);

    int get_difference(const Mpz& cd1, const Mpz& cd2);

};


#endif //PAILLER_DATAHIDER_H
