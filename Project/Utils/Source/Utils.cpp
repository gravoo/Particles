#include <Utils.hpp>
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

std::string read_file(std::string path)
{
    std::string line;
    std::string file;
    std::ifstream myfile(path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            file.append(line);
        }
        myfile.close();
    }
    return file;
}
