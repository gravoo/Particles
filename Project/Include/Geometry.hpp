#pragma once
#include<vector>

class Geometry
{
public:
    Geometry();
    unsigned int get_Vertex_Array_Object(unsigned int index);
    void generate_and_bind_buffered_objects();
    void generate_and_bind_buffered_and_element_objects();
    ~Geometry();
private:
    unsigned int VAO[2];
    unsigned int VBO[2];
    unsigned int EBO;
    std::vector<float> vertices;
    std::vector<float> verticesA;
    std::vector<unsigned int> indices;
};

