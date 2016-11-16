#include <stdio.h>
#include <stdlib.h>
#include <Graphic.hpp>
#include <iostream>

void resizeFunction(Graphic *graphic, int Width, int Height)
{
    graphic->ResizeFunction(Width, Height);
}

Graphic::Graphic(int argc, char *argv[])
{
    m_windowHandle = initWindowHandle(argc, argv);
    m_glewInitResult = glewInit();
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(RenderFunction);
    fprintf(stdout, "INFO: OpenGL Version: %s\n all system are workig correctly", glGetString(GL_VERSION));
    glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
    glutMainLoop();
    exit(EXIT_SUCCESS);
}

int Graphic::initWindowHandle(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    auto l_windowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX.c_str());
    if (l_windowHandle < 1)
    {
        fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
        exit(EXIT_FAILURE);
    }
    return l_windowHandle;
}
GLenum Graphic::initGlew()
{
    auto l_glewInitResult = glewInit();
    if (GLEW_OK != l_glewInitResult)
    {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(l_glewInitResult));
        exit(EXIT_FAILURE);
    }
    return l_glewInitResult;
}
