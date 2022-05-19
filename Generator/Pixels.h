#pragma once
#include "includes.h"
#include <vector>

typedef int P;

class Pixels;

struct Pixel {
    P x;
    P y;
    Pixel() = default;
    Pixel(P x_, P y_) {
        x = x_;
        y = y_;
    }
    Pixel(const Pixel& p) : Pixel(p.x, p.y) {}
};

class Pixels {
private:
    std::vector<Pixel> pixels_;
public:
    typedef int P;
    Pixels() = default;
    Pixels(Pixels& m) = default;
    Pixels(Pixels&& m) = default;
    void add(P x, P y) {
        Pixel pixel;
        pixel.x = x;
        pixel.y = y;
        pixels_.push_back(pixel);
    }
    void pop() {
        pixels_.pop_back();
    }
    void modify(size_t i, P x, P y) {  
        if (i >= pixels_.size()) {
            throw "Pixel out of range";
        }
        pixels_[i].x = x;
        pixels_[i].y = y;
    }
    Pixel pixel(size_t i) {
        if (i >= pixels_.size()) {
            throw "Pixel out of range";
        }
        return pixels_[i];
    }
    size_t count() {
        return pixels_.size();
    }
    void clear() {
        pixels_ = {};
    }
};