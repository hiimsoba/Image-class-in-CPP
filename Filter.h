#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Filter {
public:
    // attributes
    std::string name;
    int width = 0, height = 0;
    std::vector<std::vector<double>> values;
    double factor = 1, bias = 0;
    // constructor, destructor
    Filter(std::string, int, int);
    Filter(std::string);
    Filter();
    ~Filter();
    // methods
    void initEmptyFilter();
    void loadFilter(std::string);
};

#endif // FILTER_H
