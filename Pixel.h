#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
    // members
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    // constructor and destructor
    Pixel();
    ~Pixel();
    // methods
    unsigned char brightness();
    void Set(unsigned char, unsigned char, unsigned char);
    void Set(unsigned char);
    void Set();
    void print();
};

#endif // PIXEL_H
