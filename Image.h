#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "Pixel.h"
#include "Filter.h"

class Image {
public:
    // members
    int width, height;
    int range = 255;
    std::vector<std::vector<Pixel>> pixels;
    // constructor and destructor
    Image();
    Image(int, int);
    ~Image();
    // methods
    void makeEmptyImage();
    void readPPM(std::string);
    void writePPM(std::string);
    void readImageFile(std::string, std::string);
    void createImageFile(std::string, std::string);
    void applyFilter(Filter);
    void turnToGrayscale();
};

#endif
