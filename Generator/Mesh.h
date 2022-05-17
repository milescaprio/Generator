#pragma once
#include "includes.h"
#include <vector>

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
    Point point(size_t i) {
        return mesh_[i];
    }
    size_t count() {
        return mesh_.size();
    }
    void clear() {
        mesh_ = {};
    }
    void rotate(float midx, float midy, float ang);
};