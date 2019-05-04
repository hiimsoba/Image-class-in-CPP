#include "Image.h"
#include "Pixel.h"
#include "Filter.h"

#include <thread>

// image things

Image::Image() {
    // empty constructor
    width = 0;
    height = 0;
}

Image::Image(int width_, int height_) {
    width = width_;
    height = height_;
    makeEmptyImage();
}

Image::~Image() {
    // destructor, idk.
}

void Image::makeEmptyImage() {
    pixels.assign(height, std::vector<Pixel> (width, Pixel()));
}

void Image::readPPM(std::string filename) {
    std::ifstream inp(filename.c_str(), std::ios::in | std::ios::binary);
    if(inp.is_open()) {
        std::string line;
        getline(inp, line);
        if(line != "P6") {
            std::cout << "Error. Unrecognized file format." << std::endl;
            return;
        }
        getline(inp, line);
        while(line[0] == '#') {
            getline(inp, line);
        }
        std::stringstream dimensions(line);
        try {
            dimensions >> width;
            dimensions >> height;
            makeEmptyImage();
        } catch(std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
            return;
        }
        getline(inp, line);
        std::stringstream max_val(line);
        try {
            max_val >> range;
        } catch(std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
            return;
        }
        char aux;
        unsigned char r, g, b;
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                inp.read(&aux, 1);
                r = (unsigned char) aux;
                inp.read(&aux, 1);
                g = (unsigned char) aux;
                inp.read(&aux, 1);
                b = (unsigned char) aux;
                pixels[y][x].Set(r, g, b);
            }
        }
    } else {
        std::cout << "Error. Unable to open " << filename << std::endl;
    }
    inp.close();
}

void Image::writePPM(std::string filename) {
    std::ofstream inp(filename.c_str(), std::ios::out | std::ios::binary);
    if(inp.is_open()) {
        inp << "P6\n";
        inp << width;
        inp << " ";
        inp << height << "\n";
        inp << range << "\n";
        char aux;
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                aux = (unsigned char) pixels[y][x].r;
                inp.write(&aux, 1);
                aux = (unsigned char) pixels[y][x].g;
                inp.write(&aux, 1);
                aux = (unsigned char) pixels[y][x].b;
                inp.write(&aux, 1);
            }
        }
    } else {
        std::cout << "Error. Unable to open " << filename << std::endl;
    }
    inp.close();
}

void Image::readImageFile(std::string filename, std::string extension) {
    system(("magick " + filename + "." + extension + " " + filename + ".ppm").c_str());
    readPPM(filename + ".ppm");
    remove((filename + ".ppm").c_str());
}

void Image::createImageFile(std::string filename, std::string extension) {
    writePPM(filename + ".ppm");
    system(("magick " + filename + ".ppm " + filename + "." + extension).c_str());
    remove((filename + ".ppm").c_str());
}

void Image::applyFilter(Filter f) {
    Image result(width, height);
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            double red = 0.0, green = 0.0, blue = 0.0;
            for(int fY = 0; fY < f.height; fY++) {
                for(int fX = 0; fX < f.width; fX++) {
                    int imageX = (x - f.width / 2 + fX + width) % width;
                    int imageY = (y - f.height / 2 + fY + height) % height;
                    red += pixels[imageY][imageX].r * f.values[fY][fX];
                    green += pixels[imageY][imageX].g * f.values[fY][fX];
                    blue += pixels[imageY][imageX].b * f.values[fY][fX];
                }
            }
            result.pixels[y][x].r = std::min(std::max(int(f.factor * red + f.bias), 0), 255);
            result.pixels[y][x].g = std::min(std::max(int(f.factor * green + f.bias), 0), 255);
            result.pixels[y][x].b = std::min(std::max(int(f.factor * blue + f.bias), 0), 255);
        }
    }
    pixels = result.pixels;
}

void Image::turnToGrayscale() {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            pixels[y][x].Set(pixels[y][x].brightness());
        }
    }
}
