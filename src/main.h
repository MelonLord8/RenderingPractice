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

#define NUM_SPHERES 10
#define LOD 10
#define RADIUS 0.1 

int main();
unsigned int make_module(const string& filepath, unsigned int module_type);
unsigned int make_shader_program(const string& vertex_shader_filepath, const string& fragment_shader_filepath);

float random_float(const float &min, const float &max);