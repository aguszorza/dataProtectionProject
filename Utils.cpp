#include "Utils.h"

std::vector< std::vector<Mpz> > Utils::paillierEncodeMatrix(const std::vector< std::vector<Mpz> >& matrix,
        const Paillier& paillier, Generator& generator_r1, const int& column_1, const int& column_2) {
    std::vector< std::vector<Mpz> > result;
    Mpz r;
    for (unsigned int row = 0; row < matrix.size(); row++) {
        r = generator_r1.generate_prime(10, 24);
        result.push_back(matrix[row]);
        result[row][column_1] = paillier.encode(result[row][column_1], r);
        result[row][column_2] = paillier.encode(result[row][column_2], r);
    }
    return result;
}

std::vector< std::vector<Mpz> > Utils::paillierVoidEncrypting(const std::vector< std::vector<Mpz> >& matrix,
        const Paillier& paillier, Generator& generator_r2, const int& column_1, const int& column_2) {
    std::vector< std::vector<Mpz> > result;
    Mpz r2;
    for (unsigned int row = 0; row < matrix.size(); row++) {
        result.push_back(matrix[row]);
        r2 = generator_r2.generate_prime(10, 24);
        result[row][column_2] = (result[row][column_2] * paillier.encode(0, r2)).mod(paillier.N2);
    }
    return result;
}

std::vector< std::vector<Mpz> > Utils::getEncryptedDifferences(const std::vector< std::vector<Mpz> >& matrix,
        const DataHider& dataHider, const int& column_1, const int& column_2) {
    std::vector< std::vector<Mpz> > result;
    for (unsigned int row = 0; row < matrix.size(); row++) {
        result.push_back(matrix[row]);
        std::list<Mpz> list = dataHider.get_encrypted_differences(result[row][column_1], result[row][column_2]);
        result[row][column_1] = list.front();
        result[row][column_2] = list.back();
    }
    return result;
}

std::vector<Difference> Utils::getDifferences(const std::vector< std::vector<Mpz> >& matrix, const DataHider& dataHider,
        const int& column_1, const int& column_2) {
    std::vector<Difference> result;
    for (unsigned int row = 0; row < matrix.size(); row++) {
        Difference d = dataHider.get_difference(matrix[row][column_1], matrix[row][column_2]);
        result.push_back(d);
    }
    return result;
}

Histogram Utils::generateHistogram(const std::vector<Difference>& differences, const DataHider& dataHider,
        const int& column_1, const int& column_2) {
    Histogram histogram;
    for (unsigned int position = 0; position < differences.size(); position++) {
        histogram.add(differences[position].difference);
    }
    return histogram;
}

std::vector< std::vector<Mpz> > Utils::addTattoo(const std::vector< std::vector<Mpz> >& matrix,
        const std::vector<Difference>& differences, TattooAggregator& tattooAggregator, const int& EP,
        const int& column_1, const int& column_2) {
    std::vector< std::vector<Mpz> > result;
    for (unsigned int row = 0; row < matrix.size(); row++) {
        result.push_back(matrix[row]);
        std::list<Mpz> list = tattooAggregator.tattoo(result[row][column_1], result[row][column_2], differences[row], EP);
        result[row][column_1] = list.front();
        result[row][column_2] = list.back();
    }
    return result;
}
