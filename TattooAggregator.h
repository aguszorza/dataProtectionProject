#ifndef PAILLER_TATTOOAGGREGATOR_H
#define PAILLER_TATTOOAGGREGATOR_H

#include <list>
#include <bitset>
#include "Mpz.h"
#include "Difference.h"

class TattooAggregator {
private:
    Mpz g;
    Mpz N2;
    std::bitset<128> tattoo_data;
    unsigned int tattoo_position;

public:
    TattooAggregator(const Mpz& g, const Mpz& N2, std::string& tattoo);

    ~TattooAggregator();

    std::list<Mpz> tattoo(const Mpz& c1, const Mpz& c2, const Difference& difference, const int& EP);

    std::list<Mpz> removeTattoo(const Mpz& cw1, const Mpz& cw2, const Difference& difference, const int& EP);

    std::list<Mpz> removeAdditionalData(const Mpz& cw1, const Mpz& cw2, const Difference& difference, const int& EP);

    void getTattooBit(std::string& tattoo, const Difference& difference, const int& EP);

    std::string getAddedTattoo();
};


#endif //PAILLER_TATTOOAGGREGATOR_H
