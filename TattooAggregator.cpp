#include "TattooAggregator.h"


TattooAggregator::TattooAggregator(Mpz& g, std::string& tattoo) {
    this->g = g;
    this->tattoo_position = 0;

    std::string s2;
    for (int pos = tattoo.size() - 1; pos >= 0; pos--) {
        s2.push_back(tattoo[pos]);
    }
    this->tattoo_data = std::bitset<128>(s2);
}

TattooAggregator::~TattooAggregator() {}

std::list<Mpz> TattooAggregator::tattoo(const Mpz& c1, const Mpz& c2, const Difference& difference, const int& EP) {
    int power = 0;
    std::list<Mpz> result;
    Mpz cw1 = c1;
    Mpz cw2 = c2;


    if (difference.difference > EP) {
        power = 1;
    } else if (difference.difference == EP) {
        power = this->tattoo_data[this->tattoo_position];
        this->tattoo_position  += 1;
    }

    if (difference.sign > 0) {
        cw1 = cw1 * g.pow(power);
    } else {
        cw2 = cw2 * g.pow(power);
    }
    result.push_back(cw1);
    result.push_back(cw2);

    return result;
}
