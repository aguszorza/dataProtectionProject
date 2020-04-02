#ifndef PAILLER_PARSER_H
#define PAILLER_PARSER_H

#include <string>
#include "Mpz.h"

class Parser {
private:
    int columns;
    int rows;
    int column_1;
    int column_2;
    int EP;
    std::string file;
    std::string tattoo;
    std::string process;
    unsigned long int KS;
    Mpz p;
    Mpz q;

    /* Validations */
    void validateTattoo();

    void validateColumns();

    void validateRows();

    void validateColumn1();

    void validateColumn2();

    void validateColumnDifference();

    void validateFile();

    void validateProcess();

    void validateEP();

    void validatePQ();

public:
    Parser(int argc, char *argv[]);

    ~Parser();

    /* Getters of the attributes. If they are in an invalid value, it returns the default value */
    int getColumns(int defaultValue);

    int getRows(int defaultValue);

    int getColumn1(int defaultValue);

    int getColumn2(int defaultValue);

    std::string getTattoo(std::string defaultValue);

    unsigned long int getKs(unsigned long int defaultValue);

    std::string getFilename(std::string defaultValue);

    bool getDoEncodeProcess(bool defaultValue);

    bool getDoDecodeProcess(bool defaultValue);

    int getEP();

    Mpz getP(Mpz& defaultValue);

    Mpz getQ(Mpz& defaultValue);
};


#endif //PAILLER_PARSER_H
