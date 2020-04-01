#include "Parser.h"
#include <sstream>

Parser::Parser(int argc, char *argv[]) {
    std::string argument;
    this->columns = -1;
    this->rows = -1;
    this->column_1 = -1;
    this->column_2 = -1;
    this->tattoo = "invalid";
    this->KS = 0; // We suppose that 0 is an invalid key
    this->file = "";
    for (int i = 1; i < argc; i += 2) {
        argument = std::string(argv[i]);
        if(argument == "-columns") {
            std::istringstream(argv[i + 1]) >>  this->columns;
        } else if (argument == "-rows") {
            std::istringstream(argv[i + 1]) >> this->rows;
        } else if (argument == "-column_1") {
            std::istringstream(argv[i + 1]) >> this->column_1;
        } else if (argument == "-column_2") {
            std::istringstream(argv[i + 1]) >> this->column_2;
        } else if (argument == "-tattoo") {
            this->tattoo = argv[i + 1];
        } else if (argument == "-ks") {
            std::istringstream(argv[i + 1]) >> this->KS;
        } else if (argument == "-file") {
            this->file = argv[i + 1];
        }
    }
}

Parser::~Parser() {}

int Parser::getColumns(int defaultValue) {
    if (this->columns == -1) {
        return defaultValue;
    }
    return this->columns;
}

int Parser::getRows(int defaultValue) {
    if (this->rows == -1) {
        return defaultValue;
    }
    return this->rows;
}

int Parser::getColumn1(int defaultValue) {
    if (this->column_1 == -1) {
        return defaultValue;
    }
    return this->column_1;
}

int Parser::getColumn2(int defaultValue) {
    if (this->column_2 == -1) {
        return defaultValue;
    }
    return this->column_2;
}

std::string Parser::getTattoo(std::string defaultValue) {
    if (this->tattoo == "invalid") {
        return defaultValue;
    }
    return this->tattoo;
}

unsigned long int Parser::getKs(unsigned long int defaultValue) {
    if (this->KS == 0) {
        return defaultValue;
    }
    return this->KS;
}

std::string Parser::getFilename(std::string defaultValue) {
    if (this->file == "") {
        return defaultValue;
    }
    return this->file;
}
