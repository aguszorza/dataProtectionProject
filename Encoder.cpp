#include "Encoder.h"
#include "TattooAggregator.h"
#include "Paillier.h"
#include "DataHider.h"
#include "Generator.h"
#include "Histogram.h"
#include "Utils.h"

std::string EMPTY_TATTOO = "";

Encoder::Encoder(std::string& tattoo, unsigned long int& KS, int& column1, int& column2) {
    this->tattoo = tattoo;
    this->KS = KS;
    this->column1 = column1;
    this->column2 = column2;
}

Encoder::~Encoder() {}

Matrix Encoder::encode(const Mpz& p, const Mpz& q, const Matrix& matrix, int& EP) {
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz g = N + 1;
    TattooAggregator tattooAggregator(g, N2, this->tattoo);
    Paillier paillier(p, q);
    DataHider dataHider(p, q);

    Generator generator_r1;
    Generator generator_r2(this->KS);

    std::vector<Difference> d_list;
    Histogram histogram;

    Matrix c_matrix, cd_matrix, final_matrix;

    Utils::printTitle("Starting encoding");

    c_matrix = Utils::paillierEncodeMatrix(matrix, paillier, generator_r1, this->column1, this->column2);
    cd_matrix = Utils::getEncryptedDifferences(c_matrix, dataHider, this->column1, this->column2);
    d_list = Utils::getDifferences(cd_matrix, dataHider, this->column1, this->column2);

    histogram = Utils::generateHistogram(d_list, dataHider, this->column1, this->column2);

    EP = histogram.get_max_key();
    final_matrix = Utils::addTattoo(c_matrix, d_list, tattooAggregator, EP, this->column1, this->column2);
    std::cout << "Added tattoo = " << tattooAggregator.getAddedTattoo() << std::endl;
    final_matrix = Utils::paillierVoidEncrypting(final_matrix, paillier, generator_r2, this->column1, this->column2);

    Utils::saveMatrixInCsv("./output/encoded_paillier", c_matrix);
    Utils::saveMatrixInCsv("./output/encoded_differences", cd_matrix);
    Utils::saveMatrixInCsv("./output/encoded_with_tattoo", final_matrix);

    return final_matrix;
}

Matrix Encoder::decode_3_3_1(const Mpz& p, const Mpz& q, const Matrix& matrix, const int& EP) {
    Generator generator_r2(this->KS);
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz g = N + 1;

    TattooAggregator tattooAggregator(g, N2, EMPTY_TATTOO);
    Paillier paillier(p, q);
    DataHider dataHider(p, q);

    std::vector<Difference> d_list;
    Matrix c_matrix, cw_matrix, cdw_matrix, decoded_matrix;

    cw_matrix = Utils::paillierRemoveVoidEncrypting(matrix, paillier, generator_r2, this->column1, this->column2);
    cdw_matrix = Utils::getEncryptedDifferences(cw_matrix, dataHider, this->column1, this->column2);
    d_list = Utils::getDifferences(cdw_matrix, dataHider, this->column1, this->column2);

    std::cout << "Added tattoo = " << Utils::getTattoo(d_list, tattooAggregator, EP) << std::endl;
    // we get c1 and c2
    c_matrix = Utils::removeTattoo(cw_matrix, d_list, tattooAggregator, EP, this->column1, this->column2);

    decoded_matrix = Utils::paillierDecodeMatrix(c_matrix, paillier, this->column1, this->column2);

    return decoded_matrix;
}

Matrix Encoder::decode_3_3_2(const Mpz& p, const Mpz& q, const Matrix& matrix, const int& EP) {
    Generator generator_r2(this->KS);
    Mpz N = p * q;
    Mpz N2 = N * N;
    Mpz g = N + 1;

    TattooAggregator tattooAggregator(g, N2, EMPTY_TATTOO);
    Paillier paillier(p, q);
    DataHider dataHider(p, q);

    std::vector<Difference> d_list;
    Matrix pw_matrix, cw_matrix, cdw_matrix, decoded_matrix;

    cw_matrix = Utils::paillierRemoveVoidEncrypting(matrix, paillier, generator_r2, this->column1, this->column2);
    pw_matrix = Utils::paillierDecodeMatrix(cw_matrix, paillier, this->column1, this->column2);

    d_list = Utils::getDecodedDifferences(pw_matrix, this->column1, this->column2);
    std::cout << "Added tattoo = " << Utils::getTattoo(d_list, tattooAggregator, EP) << std::endl;

    decoded_matrix = Utils::removeAdditionalData(pw_matrix, d_list, tattooAggregator, EP, this->column1, this->column2);

    return decoded_matrix;
}
