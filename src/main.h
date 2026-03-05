#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include "Triangle.h"
#include "Sphere.h"

using namespace std;

#define NUM_SPHERES 128
#define LOD 16
#define RADIUS 0.05 

int main();
unsigned int make_module(const string& filepath, unsigned int module_type);
unsigned int make_shader_program(const string& vertex_shader_filepath, const string& fragment_shader_filepath);

float random_float(const float &min, const float &max);

void send_data_to_gpu(const vector<Sphere*> &spheres, unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int &num_elements);
void draw(const unsigned int &VAO, const unsigned int &num_elements);
void deallocate_buffers(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);