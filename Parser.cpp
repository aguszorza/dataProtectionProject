#include "Parser.h"
#include <sstream>
#include <fstream>

Parser::Parser(int argc, char *argv[]) {
    std::string argument;
    this->columns = -1;
    this->rows = -1;
    this->column_1 = -1;
    this->column_2 = -1;
    this->tattoo = "invalid";
    this->KS = 0; // We suppose that 0 is an invalid key
    this->file = "";
    this->process = "";
    this->EP = -1;
    this->p = 0;
    this->q = 0;

    for (int i = 1; i < argc; i += 2) {
        argument = std::string(argv[i]);
        if(argument == "-columns") {
            std::istringstream(argv[i + 1]) >>  this->columns;
            this->validateColumns();
        } else if (argument == "-rows") {
            std::istringstream(argv[i + 1]) >> this->rows;
            this->validateRows();
        } else if (argument == "-column_1") {
            std::istringstream(argv[i + 1]) >> this->column_1;
            this->validateColumn1();
        } else if (argument == "-column_2") {
            std::istringstream(argv[i + 1]) >> this->column_2;
            this->validateColumn2();
        } else if (argument == "-tattoo") {
            this->tattoo = argv[i + 1];
            this->validateTattoo();
        } else if (argument == "-ks") {
            std::istringstream(argv[i + 1]) >> this->KS;
        } else if (argument == "-file") {
            this->file = argv[i + 1];
            this->validateFile();
        } else if (argument == "-process") {
            this->process = argv[i + 1];
            this->validateProcess();
        } else if (argument == "-EP") {
            std::istringstream(argv[i + 1]) >> this->EP;
            this->validateEP();
        } else if (argument == "-p") {
            this->p = Mpz(argv[i + 1]);
        } else if (argument == "-q") {
            this->q = Mpz(argv[i + 1]);
        }
    }
    this->validateColumnDifference();
    this->validatePQ();
}

Parser::~Parser() {}

void Parser::validateTattoo() {
    if (this->tattoo.size() > 128) {
        throw std::runtime_error("Invalid size Tattoo: the size should be less than 128");
    }
    for (std::string::iterator it = this->tattoo.begin(); it != this->tattoo.end(); it++) {
        if (*it != '0' && *it != '1') {
            throw std::runtime_error("Invalid value Tattoo: the tattoo can only be binary");
        }
    }
}

void Parser::validateColumns() {
    if (this->columns < 2) {
        throw std::runtime_error("Invalid value Columns: it should have a positive value");
    }
}

void Parser::validateRows() {
    if (this->rows < 2) {
        throw std::runtime_error("Invalid value Rows: it should have a positive value");
    }
}

void Parser::validateColumn1() {
    if (this->column_1 < 0) {
        throw std::runtime_error("Invalid value Column 1: it should not have a negative value");
    }
}

void Parser::validateColumn2() {
    if (this->column_2 < 0) {
        throw std::runtime_error("Invalid value Column 2: it should not have a negative value");
    }
}

void Parser::validateColumnDifference() {
    if (this->column_1 == this->column_2 && this->column_1 != -1) {
        throw std::runtime_error("Invalid value Column 1 and 2: they should have a different value");
    }
}

void Parser::validateFile() {
    std::ifstream matrixFile(this->file.c_str());
    if (!matrixFile.good()) {
        throw std::runtime_error("Invalid file: the file does not exist");
    }
    matrixFile.close();
}

void Parser::validateProcess() {
    if (this->process != "e" and this->process != "ed" and this->process != "d") {
        return;
    }
    if (this->file.empty() and this->process == "d") {
        throw std::runtime_error("Invalid process: decoding requires encoded matrix file");
    }
}

void Parser::validateEP() {
    if (this->process != "e" and this->process != "ed" and this->process != "d") {
        return;
    }
    if (this->EP == -1 and this->process == "d") {
        throw std::runtime_error("Invalid EP: decoding requires a positive EP");
    }
}

void Parser::validatePQ() {
    if (this->process != "e" and this->process != "ed" and this->process != "d") {
        return;
    }
    if (this->process == "d" and (this->p == 0 or this->q == 0)) {
        throw std::runtime_error("Invalid q or p: decoding requires a positive p and q");
    }
}

int Parser::getColumns(int defaultValue) {
    if (this->columns < 2) {
        return defaultValue;
    }
    return this->columns;
}

int Parser::getRows(int defaultValue) {
    if (this->rows < 2) {
        return defaultValue;
    }
    return this->rows;
}

int Parser::getColumn1(int defaultValue) {
    if (this->column_1 < 0) {
        return defaultValue;
    }
    return this->column_1;
}

int Parser::getColumn2(int defaultValue) {
    if (this->column_2 < 0) {
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
    if (this->file.empty()) {
        return defaultValue;
    }
    return this->file;
}

bool Parser::getDoEncodeProcess(bool defaultValue) {
    if (this->process != "e" and this->process != "ed" and this->process != "d") {
        return defaultValue;
    }
    return this->process == "e" or this->process == "ed";
}

bool Parser::getDoDecodeProcess(bool defaultValue) {
    if (this->process != "e" and this->process != "ed" and this->process != "d") {
        return defaultValue;
    }
    return this->process == "d" or this->process == "ed";
}

int Parser::getEP() {
    return this->EP;
}

Mpz Parser::getP(Mpz& defaultValue) {
    if (this->p < 1) {
        return defaultValue;
    }
    return this->p;
}

Mpz Parser::getQ(Mpz& defaultValue) {
    if (this->q < 1) {
        return defaultValue;
    }
    return this->q;
}
