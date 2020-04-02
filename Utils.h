#ifndef PAILLER_UTILS_H
#define PAILLER_UTILS_H

#include <vector>
#include <string>
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
    /* It applies Paillier to the entire matrix */
    static Matrix paillierEncodeMatrix(const Matrix& matrix, const Paillier& paillier, Generator& generator_r1,
            const int& column_1, const int& column_2);

    /* It applies Paillier to the second value using another random value r2 */
    static Matrix paillierVoidEncrypting(const Matrix& matrix, const Paillier& paillier, Generator& generator_r2,
            const int& column_1, const int& column_2);

    /* It returns the matrix with the encrypted differences */
    static Matrix getEncryptedDifferences(const Matrix& matrix, const DataHider& dataHider, const int& column_1,
            const int& column_2);

    /* It returns the differences between the two columns */
    static std::vector<Difference> getDifferences(const Matrix& matrix, const DataHider& dataHider,
            const int& column_1, const int& column_2);

    /* It generates the histogram */
    static Histogram generateHistogram(const std::vector<Difference>& differences, const DataHider& dataHider,
            const int& column_1, const int& column_2);

    /* It adds the tattoo to the entire matrix */
    static Matrix addTattoo(const Matrix& matrix, const std::vector<Difference>& differences,
            TattooAggregator& tattooAggregator, const int& EP, const int& column_1, const int& column_2);

    /* It removes the encryption in the second value that was made with r2 */
    static Matrix paillierRemoveVoidEncrypting(const Matrix& matrix, const Paillier& paillier, Generator& generator_r2,
            const int& column_1, const int& column_2);

    /* It removes the tattoo to the entire matrix */
    static Matrix removeTattoo(const Matrix& matrix, const std::vector<Difference>& differences,
            TattooAggregator& tattooAggregator, const int& EP, const int& column_1, const int& column_2);

    /* It removes the additional bits if it corresponds */
    static Matrix removeAdditionalData(const Matrix& matrix, const std::vector<Difference>& differences,
            TattooAggregator& tattooAggregator, const int& EP, const int& column_1, const int& column_2);

    /* It decodes the matrix using Paillier */
    static Matrix paillierDecodeMatrix(const Matrix& matrix, const Paillier& paillier, const int& column_1,
            const int& column_2);

    /* It returns the tattoo that was applied */
    static std::string getTattoo(const std::vector<Difference>& differences, TattooAggregator& tattooAggregator,
            const int& EP);

    /* It returns the differences decoded */
    static std::vector<Difference> getDecodedDifferences(const Matrix& matrix, const int& column_1, const int& column_2);

    /* It prints a title between * */
    static void printTitle(const std::string& title);

    /* It saves the matrix in a csv file */
    static void saveMatrixInCsv(const std::string& filename, const Matrix& matrix);

    /* It saves the matrix in a txt file */
    static void saveMatrixInTxt(const std::string& filename, const Matrix& matrix, int dataWidth);
};


#endif //PAILLER_UTILS_H
