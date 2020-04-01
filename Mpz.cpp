#include "Mpz.h"
#include <gmpxx.h>

Mpz::Mpz(int value) {
    mpz_init(this->gmp);
    mpz_set_ui(this->gmp, value);
}

Mpz::Mpz(const Mpz &other) {
    mpz_init(this->gmp);
    mpz_set(this->gmp, other.gmp);
}

Mpz::~Mpz() {
    mpz_clear(this->gmp);
}

Mpz Mpz::operator+(const Mpz& other) const {
    Mpz result;
    mpz_add(result.gmp, this->gmp, other.gmp);
    return result;
}

Mpz Mpz::operator+(const unsigned long int& value) const {
    Mpz result;
    mpz_add_ui(result.gmp, this->gmp, value);
    return result;
}

Mpz& Mpz::operator+=(const unsigned long int& value) {
    mpz_add_ui(this->gmp, this->gmp, value);
    return *this;
}

Mpz& Mpz::operator+=(const Mpz& other) {
    mpz_add(this->gmp, this->gmp, other.gmp);
    return *this;
}

Mpz Mpz::operator-(const Mpz& other) const {
    Mpz result;
    mpz_sub(result.gmp, this->gmp, other.gmp);
    return result;
}

Mpz Mpz::operator-(const unsigned long int& value) const {
    Mpz result;
    mpz_sub_ui(result.gmp, this->gmp, value);
    return result;
}

Mpz& Mpz::operator-=(const unsigned long int& value) {
    mpz_sub_ui(this->gmp, this->gmp, value);
    return *this;
}

Mpz& Mpz::operator-=(const Mpz& other) {
    mpz_sub(this->gmp, this->gmp, other.gmp);
    return *this;
}

Mpz Mpz::operator*(const Mpz& other) const {
    Mpz result;
    mpz_mul(result.gmp, this->gmp, other.gmp);
    return result;
}

Mpz Mpz::operator*(const unsigned long int& value) const {
    Mpz result;
    mpz_mul_ui(result.gmp, this->gmp, value);
    return result;
}

Mpz& Mpz::operator*=(const unsigned long int& value) {
    mpz_mul_ui(this->gmp, this->gmp, value);
    return *this;
}

Mpz& Mpz::operator*=(const Mpz& other) {
    mpz_mul(this->gmp, this->gmp, other.gmp);
    return *this;
}

Mpz Mpz::operator/(const Mpz& other) const {
    Mpz result;
    mpz_divexact(result.gmp, this->gmp, other.gmp);
    return result;
}

Mpz Mpz::operator/(const unsigned long int& value) const {
    Mpz result;
    mpz_divexact_ui(result.gmp, this->gmp, value);
    return result;
}

Mpz& Mpz::operator/=(const unsigned long int& value) {
    mpz_divexact_ui(this->gmp, this->gmp, value);
    return *this;
}

Mpz& Mpz::operator/=(const Mpz& other) {
    mpz_divexact(this->gmp, this->gmp, other.gmp);
    return *this;
}

Mpz& Mpz::operator=(const Mpz& other) {
    if (this != &other) {
        mpz_set(this->gmp, other.gmp);
    }
    return *this;
}

Mpz& Mpz::operator=(const unsigned long int& value) {
    mpz_set_ui(this->gmp, value);
    return *this;
}

bool Mpz::operator>(const unsigned long int& other) const {
    int result = mpz_cmp_ui(this->gmp , other);
    return result > 0;
}

bool Mpz::operator>(const Mpz& other) const {
    int result = mpz_cmp(this->gmp , other.gmp);
    return result > 0;
}

bool Mpz::operator<(const unsigned long int& other) const {
    int result = mpz_cmp_ui(this->gmp , other);
    return result < 0;
}

bool Mpz::operator<(const Mpz& other) const {
    int result = mpz_cmp(this->gmp , other.gmp);
    return result < 0;
}

bool Mpz::operator!=(const Mpz& other) const {
    int result = mpz_cmp(this->gmp , other.gmp);
    return result != 0;
}

bool Mpz::operator!=(const unsigned long int& other) const {
    int result = mpz_cmp_ui(this->gmp, other);
    return result != 0;
}

bool Mpz::operator==(const Mpz& other) const {
    int result = mpz_cmp(this->gmp , other.gmp);
    return result == 0;
}

bool Mpz::operator==(const unsigned long int& other) const {
    int result = mpz_cmp_ui(this->gmp, other);
    return result == 0;
}

Mpz Mpz::abs() const {
    Mpz result;
    mpz_abs(result.gmp, this->gmp);
    return result;
}

Mpz Mpz::pow(const unsigned long int& power) const {
    Mpz result;
    mpz_pow_ui(result.gmp, this->gmp, power);
    return result;
}

Mpz Mpz::powm(const Mpz& exp, const Mpz& mod) const {
    Mpz result;
    mpz_powm(result.gmp, this->gmp, exp.gmp, mod.gmp);
    return result;
}

Mpz Mpz::powm(const unsigned long int& exp, const Mpz& mod) const {
    Mpz result;
    mpz_powm_ui(result.gmp, this->gmp, exp, mod.gmp);
    return result;
}

int  Mpz::is_prime(int repetitions) {
    return mpz_probab_prime_p(this->gmp, repetitions);
}

size_t Mpz::sizeinbase(int base) {
    return mpz_sizeinbase(this->gmp, base);
}

Mpz Mpz::mod(const Mpz& d) const {
    Mpz result;
    mpz_mod(result.gmp, this->gmp, d.gmp);
    return result;
}

Mpz Mpz::mod(const unsigned long int& d) const {
    Mpz result;
    mpz_mod_ui(result.gmp, this->gmp, d);
    return result;
}

Mpz Mpz::invert(const Mpz& other) const {
    Mpz result;
    mpz_invert(result.gmp, this->gmp, other.gmp);
    return result;
}

Mpz Mpz::lcm(const Mpz& other) const {
    Mpz result;
    mpz_lcm(result.gmp, this->gmp, other.gmp);
    return result;
}

std::ostream& operator<<(std::ostream &os, const Mpz& value) {
    mpz_class a(value.gmp);
    os << a;

    return os;
}

unsigned long int Mpz::to_uint() {
    return mpz_get_ui(this->gmp);
}

signed long int Mpz::to_int() {
    return mpz_get_si(this->gmp);
}
