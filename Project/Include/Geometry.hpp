#pragma once
#include<vector>

class Geometry
{
public:
    Geometry();
    unsigned int get_Vertex_Array_Object();
    void generate_and_bind_buffered_objects();
private:
    unsigned int VAO;
    unsigned int VBO;
    std::vector<float> vertices;
};

