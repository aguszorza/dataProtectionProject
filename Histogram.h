#ifndef PAILLER_HISTOGRAM_H
#define PAILLER_HISTOGRAM_H

#include <map>

class Histogram {
private:
    std::map<int,int> histogram;

public:
    Histogram();

    ~Histogram();

    /* It increases by 1 the amount of appearances of the value in the histogram  */
    void add(const int& value);

    /* It returns the value that has more appearances in the histogram */
    int get_max_key();
};


#endif //PAILLER_HISTOGRAM_H
