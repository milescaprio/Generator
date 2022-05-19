#pragma once
#include "includes.h"
#include <vector>

class Pixels;

struct Pixel;
struct Slice {
    float x1;
    float x2;
    P y;
};

class AreaSlice {
private:
    mutable size_t nextstack_ = 0;
    mutable size_t nextpixel_ = 0;
    std::vector<Slice> stack_;
public:
    AreaSlice() = default;
    AreaSlice(AreaSlice& a) = default;
    AreaSlice(AreaSlice&& a) = default;
    void add(float x1, float x2, float y) {
        Slice slice;
        slice.x1 = x1;
        slice.x2 = x2;
        slice.y = y;
        stack_.push_back(slice);
    }
    void pop() {
        stack_.pop_back();
    }
    void modify(size_t i, float x1, float x2, float y) {  
        if (i >= stack_.size()) {
            throw "Slice out of range";
        }
        stack_[i].x1 = x1;
        stack_[i].x2 = x2;
        stack_[i].y = y;
    }
    Slice slice(size_t i) {
        if (i >= stack_.size()) {
            throw "Slice out of range";
        }
        return stack_[i];
    }
    size_t count() {
        return stack_.size();
    }
    void clear() {
        stack_ = {};
    }
    Pixels pixels();
    Pixel readPixel(); //gets next pixel for iterating without generating a full cache 
};