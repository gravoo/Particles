#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 1"

int CurrentWidth = 800, CurrentHeight = 600, WindowHandle = 0;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int Width, int Height)
{
      CurrentWidth = Width;
      CurrentHeight = Height;
      glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glutSwapBuffers();
      glutPostRedisplay();

}

class Graphic
{
    public:
        Graphic(int argc, char* argv[])
            : m_windowHandle(0)
        {
          glutInit(&argc, argv);
          glutInitContextVersion(4, 0);
          glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
          glutInitContextProfile(GLUT_CORE_PROFILE);

          glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
          glutInitWindowSize(CurrentWidth, CurrentHeight);
          glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
          m_windowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

          if( m_windowHandle < 1) {
              fprintf( stderr, "ERROR: Could not create a new rendering window.\n" );
              exit(EXIT_FAILURE);
          }
          glutReshapeFunc(ResizeFunction);
          glutDisplayFunc(RenderFunction);

          glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
          glutMainLoop();
          exit(EXIT_SUCCESS);
        }

        static void ResizeFunction(int Width, int Height)
        {
              CurrentWidth = Width;
              CurrentHeight = Height;
              glViewport(0, 0, CurrentWidth, CurrentHeight);
        }
        static void RenderFunction(void)
        {
              glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
              glutSwapBuffers();
              glutPostRedisplay();

        }
private:
        int m_windowHandle;
};

int main(int argc, char* argv[])
{
    Graphic graphicComponent(argc, argv);
}


