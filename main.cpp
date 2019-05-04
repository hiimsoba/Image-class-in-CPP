#include <bits/stdc++.h>
#include "Image.h"

using namespace std;

std::string filters_dir = "filters/";

int main() {
    Image img;
//    img.readImageFile("anime", "jpg");
//    img.readImageFile("thisone", "jpg");
    img.readImageFile("thisone", "jpg");

    Filter f;

//    f.loadFilter(filters_dir + "edges.fil");
//    f.loadFilter(filters_dir + "simple_blur.fil");
//    f.loadFilter(filters_dir + "gaussian_blur.fil");
//    f.loadFilter(filters_dir + "motion_blur.fil");
    f.loadFilter(filters_dir + "sharpen.fil");
//    f.loadFilter(filters_dir + "emboss.fil");
//    f.loadFilter(filters_dir + "more_emboss.fil");

    img.applyFilter(f);
    img.applyFilter(f);
    img.applyFilter(f);
    img.applyFilter(f);
    img.applyFilter(f);
    img.applyFilter(f);
    img.applyFilter(f);
    img.applyFilter(f);

//    img.turnToGrayscale();

    img.createImageFile("gray", "png");
    return 0;
}
