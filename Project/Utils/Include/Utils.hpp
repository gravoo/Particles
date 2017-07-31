#pragma once
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float changedMixedValue(GLFWwindow *window, float mixValue);
std::string read_file(std::string path);
