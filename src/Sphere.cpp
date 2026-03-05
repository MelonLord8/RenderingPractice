#include "Sphere.h"

Sphere::Sphere(const vector<float> &center, const float &radius, const unsigned int &LOD){
    
    vector<float> vertices;
    this-> center = center;
    for (int i = 0; i < 2*LOD - 1; i++){
        for (int j = 0; j < LOD - 1; j++){
            vertices = vector<float>{   center[0] + (float)(radius*cos(M_PI*i/LOD)*sin(2*M_PI*j/LOD)), // Vertex 1
                                        center[2] + (float)(radius*cos(2*M_PI*j/LOD)),
                                        center[1] + (float)(radius*sin(M_PI*i/LOD)*sin(2*M_PI*j/LOD)),
                                        center[0] + (float)(radius*cos(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)), // Vertex 2
                                        center[2] + (float)(radius*cos(2*M_PI*j/LOD)),
                                        center[1] + (float)(radius*sin(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)),
                                        center[0] + (float)(radius*cos(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD)), // Vertex 3
                                        center[2] + (float)(radius*cos(2*M_PI*(j + 1)/LOD)),
                                        center[1] + (float)(radius*sin(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD))};

            triangles.push_back(new Triangle(vertices, get_triangle_colour(vertices)));
            
            vertices = vector<float>{   center[0] + (float)(radius*cos(M_PI*(i + 1)/LOD)*sin(2*M_PI*(j + 1)/LOD)), // Vertex 1
                                        center[2] + (float)(radius*cos(2*M_PI*(j + 1)/LOD)),
                                        center[1] + (float)(radius*sin(M_PI*(i + 1)/LOD)*sin(2*M_PI*(j + 1)/LOD)),
                                        center[0] + (float)(radius*cos(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)), // Vertex 2
                                        center[2] + (float)(radius*cos(2*M_PI*j/LOD)),
                                        center[1] + (float)(radius*sin(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)),
                                        center[0] + (float)(radius*cos(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD)), // Vertex 3
                                        center[2] + (float)(radius*cos(2*M_PI*(j + 1)/LOD)),
                                        center[1] + (float)(radius*sin(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD))};

            triangles.push_back(new Triangle(vertices, get_triangle_colour(vertices)));
        }
    }
}

void Sphere::draw(){
    for(Triangle* triangle : triangles){
        triangle->draw();
    }
}

vector<float> Sphere::get_triangle_colour(const vector<float> &vertices){
    vector<float> normal{   (vertices[0] + vertices[3] + vertices[6]) / 3 - center[0],
                            (vertices[1] + vertices[4] + vertices[7]) / 3 - center[2],
                            (vertices[2] + vertices[5] + vertices[8]) / 3 - center[1] };
    float mag = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] = normal[0] / mag;
    normal[1] = normal[1] / mag;
    normal[2] = normal[2] / mag;
    float dot_product = normal[0] * sqrt(0.5) + normal[1] * sqrt(0.5);
    return vector<float>{
        0.15f + 0.15f * dot_product,
        0.3f + 0.3f * dot_product,
        1.0f
    };
}

Sphere::~Sphere(){
    for(Triangle* triangle : triangles){
        delete triangle;
    }
}