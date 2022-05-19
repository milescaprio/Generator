#pragma once
#include "includes.h"
#include <vector>
#include <algorithm>

class AreaSlice;

struct Point {
    float x;
    float y;
};

class Mesh {
private:
    std::vector<Point> mesh_;
public:
    Mesh() = default;
    Mesh(Mesh& m) = default;
    Mesh(Mesh&& m) = default;
    void add(float x, float y) {
        Point point;
        point.x = x;
        point.y = y;
        mesh_.push_back(point);
    }
    void add(Point p) {
        mesh_.push_back(p);
    }
    void pop() {
        mesh_.pop_back();
    }
    void modify(size_t i, float x, float y) {  
        if (i >= mesh_.size()) {
            throw "Point out of range";
        }
        mesh_[i].x = x;
        mesh_[i].y = y;
    }
    Point point(size_t i) {
        if (i >= mesh_.size()) {
            throw "Point out of range";
        }
        return mesh_[i];
    }
    size_t count() {
        return mesh_.size();
    }
    void clear() {
        mesh_ = {};
    }
    void rotate(float midx, float midy, float ang);
    bool contains(float x, float y);
    AreaSlice containment();
};