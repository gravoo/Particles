#include <Graphic.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Graphic::Graphic(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitContextVersion(4, 0);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  glutInitWindowSize(CurrentWidth, CurrentHeight);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  m_windowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX.c_str());

  if( m_windowHandle < 1) {
      fprintf( stderr, "ERROR: Could not create a new rendering window.\n" );
      exit(EXIT_FAILURE);
  }
  glutReshapeFunc(ResizeFunction);
  glutDisplayFunc(RenderFunction);
  fprintf( stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

  glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

  glutMainLoop();
  exit(EXIT_SUCCESS);
}

void Graphic::doSomething()
{

}

void Graphic::doSomethingElse()
{

}

void Graphic::ctagsNextTest()
{

}
void Graphic::lastCtagsTest()
{

}

