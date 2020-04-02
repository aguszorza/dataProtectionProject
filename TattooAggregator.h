#ifndef PAILLER_TATTOOAGGREGATOR_H
#define PAILLER_TATTOOAGGREGATOR_H

#include <list>
#include <bitset>
#include <string>
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

    /* It applies the tattoo if it correspond */
    std::list<Mpz> tattoo(const Mpz& c1, const Mpz& c2, const Difference& difference, const int& EP);

    /* It removes the tattoo if it correspond */
    std::list<Mpz> removeTattoo(const Mpz& cw1, const Mpz& cw2, const Difference& difference, const int& EP);

    /* It applies the additional bit if it corresponds */
    std::list<Mpz> removeAdditionalData(const Mpz& cw1, const Mpz& cw2, const Difference& difference, const int& EP);

    /* It adds the tattoo bit in the string if it corresponds */
    void getTattooBit(std::string& tattoo, const Difference& difference, const int& EP);

    /* It returns the portion of the tattoo that was added */
    std::string getAddedTattoo();
};


#endif //PAILLER_TATTOOAGGREGATOR_H
