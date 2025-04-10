#include "RGB.hpp"
#include <algorithm>

RGB::RGB(): red(0), green(0), blue(0), alpha(0) {}

RGB::RGB(int r, int g, int b): red(r), green(g), blue(b), alpha(255) {}

RGB::RGB(int r, int g, int b, int a): red(r), green(g), blue(b), alpha(a) {}

RGB::RGB(const RGB& other): red(other.red), green(other.green), blue(other.blue), alpha(other.alpha) {}

RGB min(RGB a, RGB b){
    RGB temp;
    temp.red = std::min(a.red, b.red);
    temp.green = std::min(a.green, b.green);
    temp.blue = std::min(a.blue, b.blue);
    temp.alpha = std::min(a.alpha, b.alpha);
    return temp;
}

RGB max(RGB a, RGB b){
    RGB temp;
    temp.red = std::max(a.red, b.red);
    temp.green = std::max(a.green, b.green);
    temp.blue = std::max(a.blue, b.blue);
    temp.alpha = std::max(a.alpha, b.alpha);
    return temp;
}

RGB& RGB::operator=(const RGB& other) {
    if (this != &other) {
        red = other.red;
        green = other.green;
        blue = other.blue;
        alpha = other.alpha;
    }
    return *this;
}

RGB& RGB::operator+=(const RGB& other){
    if (this != &other) {
        red += other.red;
        green += other.green;
        blue += other.blue;
        alpha += other.alpha;
    }
    return *this;
}

RGB& RGB::operator/=(const double x){
    red /= x;
    green /= x;
    blue /= x;
    alpha /= x;
    return *this;
}

RGB::~RGB() {}