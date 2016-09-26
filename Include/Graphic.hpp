#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

class Graphic
{
public:
    Graphic(int argc, char* argv[]);

    static void ResizeFunction(int Width, int Height)
    {
          glViewport(0, 0, Width, Height);
    }

    static void RenderFunction(void)
    {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glutSwapBuffers();
          glutPostRedisplay();
    }
    void doSomething();

private:
        int m_windowHandle;
        int CurrentWidth = 800, CurrentHeight = 600, WindowHandle = 0;
        const char* WINDOW_TITLE_PREFIX = "Particles";
};


