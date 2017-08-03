#pragma once
#include<vector>

class Geometry
{
public:
    Geometry();
    unsigned int get_Vertex_Array_Object(unsigned int index);
    void generate_and_bind_buffered_objects();
    ~Geometry();
private:
    std::vector<unsigned int> VAO;
    std::vector<unsigned int> VBO;
    std::vector<unsigned int> EBO;
    std::vector<float> vertices;
    std::vector<float> verticesA;
    std::vector<float> verticesB;
    std::vector<float> woodenWall;
    std::vector<float> cube;
    std::vector<unsigned int> indices;
};

