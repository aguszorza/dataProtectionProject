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

class Utils {
public:
    static std::vector< std::vector<Mpz> > paillierEncodeMatrix(const std::vector< std::vector<Mpz> >& matrix,
            const Paillier& paillier, Generator& generator_r1, const int& column_1, const int& column_2);

    static std::vector< std::vector<Mpz> > paillierVoidEncrypting(const std::vector< std::vector<Mpz> >& matrix,
            const Paillier& paillier, Generator& generator_r2, const int& column_1, const int& column_2);

    static std::vector< std::vector<Mpz> > getEncryptedDifferences(const std::vector< std::vector<Mpz> >& matrix,
            const DataHider& dataHider, const int& column_1, const int& column_2);

    static std::vector<Difference> getDifferences(const std::vector< std::vector<Mpz> >& matrix,
            const DataHider& dataHider, const int& column_1, const int& column_2);

    static Histogram generateHistogram(const std::vector<Difference>& differences, const DataHider& dataHider,
            const int& column_1, const int& column_2);

    static std::vector< std::vector<Mpz> > addTattoo(const std::vector< std::vector<Mpz> >& matrix,
            const std::vector<Difference>& differences, TattooAggregator& tattooAggregator, const int& EP,
            const int& column_1, const int& column_2);

    static std::vector< std::vector<Mpz> > paillierRemoveVoidEncrypting(const std::vector< std::vector<Mpz> >& matrix,
            const Paillier& paillier, Generator& generator_r2, const int& column_1, const int& column_2);

    static std::vector< std::vector<Mpz> > removeTattoo(const std::vector< std::vector<Mpz> >& matrix,
            const std::vector<Difference>& differences, TattooAggregator& tattooAggregator, const int& EP,
            const int& column_1, const int& column_2);

    static std::vector< std::vector<Mpz> > paillierDecodeMatrix(const std::vector< std::vector<Mpz> >& matrix,
            const Paillier& paillier, const int& column_1, const int& column_2);
};


#endif //PAILLER_UTILS_H
