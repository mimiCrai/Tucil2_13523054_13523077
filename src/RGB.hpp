#ifndef RGB_HPP
#define RGB_HPP

class RGB
{
private:
public:
    int red;
    int green;
    int blue;
    int alpha;
    RGB();
    RGB(int r, int g, int b);
    RGB(int r, int g, int b, int a);
    RGB(const RGB& other);
    friend RGB min(RGB a, RGB b);
    friend RGB max(RGB a, RGB b);
    RGB& operator=(const RGB& other);
    RGB& operator+=(const RGB& other);
    RGB& operator/=(const double x);
    ~RGB();
};

#endif