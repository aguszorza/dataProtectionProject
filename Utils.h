#ifndef PAILLER_UTILS_H
#define PAILLER_UTILS_H

#include <vector>
#include "Mpz.h"
#include "Generator.h"
#include "Paillier.h"
#include "DataHider.h"
#include "Histogram.h"
#include "Difference.h"
#include "TattooAggregator.h"
#include "Matrix.h"

class Utils {
public:
    static Matrix paillierEncodeMatrix(const Matrix& matrix, const Paillier& paillier, Generator& generator_r1,
            const int& column_1, const int& column_2);

    static Matrix paillierVoidEncrypting(const Matrix& matrix, const Paillier& paillier, Generator& generator_r2,
            const int& column_1, const int& column_2);

    static Matrix getEncryptedDifferences(const Matrix& matrix, const DataHider& dataHider, const int& column_1,
            const int& column_2);

    static std::vector<Difference> getDifferences(const Matrix& matrix, const DataHider& dataHider,
            const int& column_1, const int& column_2);

    static Histogram generateHistogram(const std::vector<Difference>& differences, const DataHider& dataHider,
            const int& column_1, const int& column_2);

    static Matrix addTattoo(const Matrix& matrix, const std::vector<Difference>& differences,
            TattooAggregator& tattooAggregator, const int& EP, const int& column_1, const int& column_2);

    static Matrix paillierRemoveVoidEncrypting(const Matrix& matrix, const Paillier& paillier, Generator& generator_r2,
            const int& column_1, const int& column_2);

    static Matrix removeTattoo(const Matrix& matrix, const std::vector<Difference>& differences,
            TattooAggregator& tattooAggregator, const int& EP, const int& column_1, const int& column_2);

    static Matrix paillierDecodeMatrix(const Matrix& matrix, const Paillier& paillier, const int& column_1,
            const int& column_2);

    static std::string getTattoo(const std::vector<Difference>& differences, TattooAggregator& tattooAggregator,
            const int& EP);
};


#endif //PAILLER_UTILS_H
