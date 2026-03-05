#pragma once
#include "triangle.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
class Sphere{
    public:
        Sphere(const vector<float> &center, const float &radius, const unsigned int &LOD);
        ~Sphere();
        vector<float> center;
        vector<float> vertex_data;
        vector<unsigned int> triangle_elements;

    private:
        vector<float> get_vertex_colour(const vector<float>& vertex);
};