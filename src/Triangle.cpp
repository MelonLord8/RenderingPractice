#include "Triangle.h"

Triangle::Triangle(const vector<float> &vertices, const vector<float> &color){
    vertex_count = 3;
    vector<float> data{ vertices[0], vertices[1], vertices[2], color[0], color[1], color[2],
                        vertices[3], vertices[4], vertices[5], color[0], color[1], color[2],
                        vertices[6], vertices[7], vertices[8], color[0], color[1], color[2]};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
}

void Triangle::draw(){
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
} 

Triangle::~Triangle(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}