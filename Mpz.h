#ifndef PAILLER_MPZ_H
#define PAILLER_MPZ_H

#include <gmp.h>
#include <iostream>


class Mpz {
public:
    mpz_t gmp;

    /* Builder */
    Mpz(int value = 0);

    Mpz(std::string value);

    Mpz(const Mpz &other);

    /* Destroyer */
    ~Mpz();

    /* overwrite operator + */
    Mpz operator+(const unsigned long int& value) const;

    Mpz operator+(const Mpz& other) const;

    Mpz& operator+=(const unsigned long int&);

    Mpz& operator+=(const Mpz&);

    /* overwrite operator - */
    Mpz& operator-=(const unsigned long int&);

    Mpz& operator-=(const Mpz&);

    Mpz operator-(const unsigned long int& value) const;

    Mpz operator-(const Mpz& other) const;

    /* overwrite operator * */
    Mpz& operator*=(const unsigned long int&);

    Mpz& operator*=(const Mpz&);

    Mpz operator*(const unsigned long int& value) const;

    Mpz operator*(const Mpz& other) const;

    /* Exact division */
    Mpz operator/(const Mpz& other) const;

    Mpz operator/(const unsigned long int& value) const;

    Mpz& operator/=(const unsigned long int&);

    Mpz& operator/=(const Mpz&);

    /* overwrite operator = */
    Mpz& operator=(const Mpz& other);

    Mpz& operator=(const unsigned long int& value);

    /* overwrite comparison operators */
    bool operator>(const unsigned long int& other) const;

    bool operator>(const Mpz& other) const;

    bool operator<(const unsigned long int& other) const;

    bool operator<(const Mpz& other) const;

    bool operator!=(const Mpz& other) const;

    bool operator!=(const unsigned long int& other) const;

    bool operator==(const Mpz& other) const;

    bool operator==(const unsigned long int& other) const;

    /* It returns the absolute value */
    Mpz abs() const;

    /* power */
    Mpz pow(const unsigned long int& power) const;

    Mpz powm(const Mpz& exp, const Mpz& mod) const;

    Mpz powm(const unsigned long int& exp, const Mpz& other) const;

    /* Determines if the value is prime. Returns 2 if it is definitely prime, 1 if it is probably
     * prime (without being certain), or return 0 if it is definitely non-prime */
    int is_prime(int repetitions);

    /* Return the size of op measured in number of digits in the given base */
    size_t sizeinbase(int base);

    /* It calculates the module */
    Mpz mod(const Mpz& d) const;

    Mpz mod(const unsigned long int& d) const;

    /* It calculates the modular multiplicative inverse */
    Mpz invert(const Mpz& other) const;

    /* Calculate the least common multiple */
    Mpz lcm(const Mpz& other) const;

    /* It returns the number in unsigned long int */
    unsigned long int to_uint();

    /* It returns the number in long int */
    signed long int to_int();

    /* It defines how to print the class */
    friend std::ostream& operator<<(std::ostream &os, const Mpz& value);
};


#endif //PAILLER_MPZ_H

