#ifndef PAILLER_PARSER_H
#define PAILLER_PARSER_H

#include <string>

class Parser {
private:
    int columns;
    int rows;
    int column_1;
    int column_2;
    std::string file;
    std::string tattoo;
    unsigned long int KS;

    void validateTattoo();

    void validateColumns();

    void validateRows();

    void validateColumn1();

    void validateColumn2();

    void validateColumnDifference();

public:
    Parser(int argc, char *argv[]);

    ~Parser();

    int getColumns(int defaultValue);

    int getRows(int defaultValue);

    int getColumn1(int defaultValue);

    int getColumn2(int defaultValue);

    std::string getTattoo(std::string defaultValue);

    unsigned long int getKs(unsigned long int defaultValue);

    std::string getFilename(std::string defaultValue);
};


#endif //PAILLER_PARSER_H
