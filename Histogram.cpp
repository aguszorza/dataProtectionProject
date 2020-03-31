#include "Histogram.h"

Histogram::Histogram() {}

Histogram::~Histogram() {}

void Histogram::add(const int& value) {
    if (this->histogram.find(value) == this->histogram.end()) {
        this->histogram.insert(std::pair<int,int>(value, 0));
    }
    this->histogram[value] += 1;
}

int Histogram::get_max_key() {
    int max_value = -1;
    int EP = -1;
    for (std::map<int,int>::iterator it = this->histogram.begin(); it != this->histogram.end(); it++) {
        if (it->second > max_value) {
            EP = it->first;
            max_value = it->second;
        }
    }
    return EP;
}