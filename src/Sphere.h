#pragma once
#include "triangle.h"
#include <vector>
#include <cmath>
#include <iostream>
# define M_PI   3.14159265358979323846
using namespace std;
class Sphere{
    public:
        Sphere(const vector<float> &center, const float &radius, const unsigned int &LOD);
        void draw();
        ~Sphere();
        vector<float> center;
    private:
        vector<Triangle*> triangles;
        vector<float> get_triangle_colour(const vector<float> &vertices);
        
};