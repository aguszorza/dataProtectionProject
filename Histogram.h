#ifndef PAILLER_HISTOGRAM_H
#define PAILLER_HISTOGRAM_H

#include <map>

class Histogram {
private:
    std::map<int,int> histogram;

public:
    Histogram();

    ~Histogram();

    void add(const int& value);

    int get_max_key();
};


#endif //PAILLER_HISTOGRAM_H
