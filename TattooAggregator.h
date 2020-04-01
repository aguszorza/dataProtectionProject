#ifndef PAILLER_TATTOOAGGREGATOR_H
#define PAILLER_TATTOOAGGREGATOR_H

#include <list>
#include <bitset>
#include "Mpz.h"
#include "Difference.h"

class TattooAggregator {
private:
    Mpz g;
    std::bitset<128> tattoo_data;
    unsigned int tattoo_position;

public:
    TattooAggregator(Mpz& g, std::string& tattoo);

    ~TattooAggregator();

    std::list<Mpz> tattoo(const Mpz& c1, const Mpz& c2, const Difference& difference, const int& EP);
};


#endif //PAILLER_TATTOOAGGREGATOR_H
