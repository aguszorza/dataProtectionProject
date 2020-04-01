#include "TattooAggregator.h"


TattooAggregator::TattooAggregator(const Mpz& g, const Mpz& N2, std::string& tattoo) {
    this->g = g;
    this->N2 = N2;
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

std::list<Mpz> TattooAggregator::removeTattoo(const Mpz& cw1, const Mpz& cw2, const Difference& difference,
        const int& EP) {
    std::list<Mpz> result;
    Mpz c1 = cw1;
    Mpz c2 = cw2;
    Mpz theta_g = this->g.invert(this->N2);

    if (difference.sign > 0) {
        if (difference.difference > EP) {
            c1 = (c1 * theta_g).mod(this->N2);
        }
    } else {
        if (difference.difference > EP) {
            c2 = (c2 * theta_g).mod(this->N2);
        }
    }
    result.push_back(c1);
    result.push_back(c2);

    return result;
}

std::list<Mpz> TattooAggregator::removeAdditionalData(const Mpz& pw1, const Mpz& pw2,
        const Difference& difference, const int& EP) {
    std::list<Mpz> result;
    Mpz p1 = pw1;
    Mpz p2 = pw2;
    int subtraction = 0;
    if (difference.difference > EP) {
        subtraction = 1;
    }
    if (difference.sign > 0) {
        p1 -= subtraction;
    } else {
        p2 -= subtraction;
    }

    result.push_back(p1);
    result.push_back(p2);

    return result;
}

void TattooAggregator::getTattooBit(std::string& tattoo, const Difference& difference, const int& EP) {
    if (difference.difference == EP) {
        tattoo += "0";
    } else if (difference.difference == EP + 1) {
        tattoo += "1";
    }
}
