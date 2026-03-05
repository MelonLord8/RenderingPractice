#include "Sphere.h"

Sphere::Sphere(const vector<float> &center, const float &radius, const unsigned int &LOD){
    this-> center = center;
    for (int i = 0; i <= 2*LOD; i++){
        for (int j = 0; j <= LOD; j++){
            double theta = M_PI*j/LOD;
            double phi = M_PI*i/LOD;
            vector<float> vertex = vector<float>{   center[0] + (float)(radius*cos(phi)*sin(theta)), 
                                                    center[2] + (float)(radius*cos(theta)),
                                                    center[1] + (float)(radius*sin(phi)*sin(theta))};

            vector<float> colour = this-> get_vertex_colour(vertex);

            this->vertex_data.insert(vertex_data.end(), vertex.begin(), vertex.end());
            this->vertex_data.insert(vertex_data.end(), colour.begin(), colour.end());
        }
    }

    for (int i = 0; i < 2*LOD; i++){
        for (int j = 0; j < LOD; j++){
            this->triangle_elements.push_back(i*(LOD + 1) + j);
            this->triangle_elements.push_back((i + 1)*(LOD + 1) + j);
            this->triangle_elements.push_back(i*(LOD + 1) + j + 1);

            this->triangle_elements.push_back((i + 1)*(LOD + 1) + j);
            this->triangle_elements.push_back(i*(LOD + 1) + j + 1);
            this->triangle_elements.push_back((i + 1)*(LOD + 1) + j + 1);
        }
    }
}

vector<float> Sphere::get_vertex_colour(const vector<float> &vertex){
    vector<float> normal{   vertex[0] - center[0],
                            vertex[1] - center[2],
                            vertex[2] - center[1] };
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

Sphere::~Sphere(){}