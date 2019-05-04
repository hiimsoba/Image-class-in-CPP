#include <iostream>
#include "Pixel.h"

Pixel::Pixel() {
    // empty constructor
}

Pixel::~Pixel() {
    // destructor. awesome.
}

void Pixel::print() {
    std::cout << r << ' ' << g << ' ' << b << ' ';
}

void Pixel::Set(unsigned char r_, unsigned char g_, unsigned char b_) {
    r = r_;
    g = g_;
    b = b_;
}

void Pixel::Set(unsigned char c) {
//    std::cout << (int) c << ' ';
    r = c;
    g = c;
    b = c;
}

void Pixel::Set() {
    r = 0;
    g = 0;
    b = 0;
}

unsigned char Pixel::brightness() {
    return (r + g + b) / 3;
}
