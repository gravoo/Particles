#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

class Graphic
{
public:
    Graphic(int argc, char* argv[]);

    static void ResizeFunction(int Width, int Height) { glViewport(0, 0, Width, Height); }
    static void RenderFunction(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutSwapBuffers();
        glutPostRedisplay();
    }
    static void timerFunction(int time)
    {
        if (time != 0)
        {
            char *tmpString = (char *)malloc(512 + 10);
            sprintf(tmpString, "%s : %d Frames Per Second @ %d x %d", "dupa", m_frameCount * 4, 800, 600);
        }
    };

private:
    int initWindowHandle(int argc, char *argv[]);
    GLenum initGlew();
    int m_windowHandle{0};
    int CurrentWidth{800}, CurrentHeight{600}, WindowHandle{0};
    static unsigned m_frameCount;
    const std::string WINDOW_TITLE_PREFIX{"Particles"};
    GLenum m_glewInitResult;
};
