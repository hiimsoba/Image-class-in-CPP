#include "Filter.h"

Filter::Filter(std::string n, int w, int h) {
    name = n;
    width = w;
    height = h;
    initEmptyFilter();
}

Filter::Filter(std::string n) {
    name = n;
}

Filter::Filter() {
    // empty constructor
}

Filter::~Filter() {
    // destructor, lul.
}

void Filter::initEmptyFilter() {
    for(int y = 0; y < height; y++) {
        values.push_back(std::vector<double> ());
        for(int x = 0; x < width; x++) {
            values[y].push_back(0);
        }
    }
}

void Filter::loadFilter(std::string filename) {
    std::ifstream inp(filename.c_str());
    if(inp.is_open()) {
        std::string line;
        getline(inp, line);
        name = line;
        getline(inp, line);
        std::stringstream dimensions(line);
        dimensions >> width;
        dimensions >> height;
        values.clear();
        double aux;
        for(int i = 0; i < height; i++) {
            values.push_back(std::vector<double> ());
            getline(inp, line);
            std::stringstream ss(line);
            for(int j = 0; j < width; j++) {
                ss >> aux;
                values[i].push_back(aux);
            }
        }
        getline(inp, line);
        std::stringstream last(line);
        last >> factor >> bias;
    } else {
        std::cout << "Error. Unable to open " << filename << std::endl;
    }
}
