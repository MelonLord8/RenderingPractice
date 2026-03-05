#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
class Triangle{
    public:
        Triangle(const vector<float> &vertices, const vector<float> &colour);
        ~Triangle();
        void draw();

    private:
        unsigned int VAO, vertex_count, VBO;
        vector<float> color;
        
};