#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
class Triangle{
    public:
        Triangle(const vector<float> &vertices);
        ~Triangle();
        void draw();

    private:
        unsigned int VBO, VAO, vertex_count;
};