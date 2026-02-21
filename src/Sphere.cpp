#include "Sphere.h"

Sphere::Sphere(const vector<float> &center, const float &radius, const unsigned int &LOD){
     
    for (int i = 0; i < 2*LOD - 1; i++){
        for (int j = 0; j < LOD - 1; j++){
            triangles.push_back(new Triangle(vector<float>{ center[0] + (float)(radius*cos(M_PI*i/LOD)*sin(2*M_PI*j/LOD)), // Vertex 1
                                                        center[1] + (float)(radius*sin(M_PI*i/LOD)*sin(2*M_PI*j/LOD)),
                                                        center[2] + (float)(radius*cos(2*M_PI*j/LOD)),
                                                        center[0] + (float)(radius*cos(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)), // Vertex 2
                                                        center[1] + (float)(radius*sin(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)),
                                                        center[2] + (float)(radius*cos(2*M_PI*j/LOD)),
                                                        center[0] + (float)(radius*cos(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD)), // Vertex 3
                                                        center[1] + (float)(radius*sin(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD)),
                                                        center[2] + (float)(radius*cos(2*M_PI*(j + 1)/LOD)),
                                                    }));
            triangles.push_back(new Triangle(vector<float>{ center[0] + (float)(radius*cos(M_PI*(i + 1)/LOD)*sin(2*M_PI*(j + 1)/LOD)), // Vertex 1
                                                        center[1] + (float)(radius*sin(M_PI*(i + 1)/LOD)*sin(2*M_PI*(j + 1)/LOD)),
                                                        center[2] + (float)(radius*cos(2*M_PI*(j + 1)/LOD)),
                                                        center[0] + (float)(radius*cos(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)), // Vertex 2
                                                        center[1] + (float)(radius*sin(M_PI*(i + 1)/LOD)*sin(2*M_PI*j/LOD)),
                                                        center[2] + (float)(radius*cos(2*M_PI*j/LOD)),
                                                        center[0] + (float)(radius*cos(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD)), // Vertex 3
                                                        center[1] + (float)(radius*sin(M_PI*i/LOD)*sin(2*M_PI*(j + 1)/LOD)),
                                                        center[2] + (float)(radius*cos(2*M_PI*(j + 1)/LOD)),
                                                    }));
        }
    }
}

void Sphere::draw(){
    for(Triangle* triangle : triangles){
        triangle->draw();
    }
}

Sphere::~Sphere(){
    for(Triangle* triangle : triangles){
        delete triangle;
    }
}