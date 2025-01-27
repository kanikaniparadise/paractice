#include <stdio.h>
#include <GL/glut.h>
GLfloat light0pos[] = { 0.0, 4.0, 10.0, 1.0 };
GLfloat light0col[] = { 0.3, 0.3, 0.3, 1.0 };
GLdouble vertex[][3] = {
  { -1.0, -1.0, -1.0 },
  { 1.0, -1.0, -1.0 },
  { 1.0, 1.0, -1.0 },
  { -1.0, 1.0, -1.0 },
  { -1.0, -1.0, 1.0 },
  { 1.0, -1.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { -1.0, 1.0, 1.0 }
};
int face[][4] = {
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};
GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};
  

float eye[4]={2,2,-2,1};



GLfloat mater[] = { 1, 1,1 , 0.3 };
GLfloat green[] = { 1.0, 2.0, 1.0, 1.0 };

void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);
  gluLookAt(4 , 4, 4, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    /* 図形の描画 */

  glBegin(GL_QUADS);
    for (int j = 0; j < 6; ++j) {
      glNormal3dv(normal[j]);

      for (int i = 0; i < 4; ++i) {
	glVertex3dv(vertex[face[j][i]]);
    }
  }
  
  glEnd();
glutSwapBuffers();

}
void resize(int w, int h)
{
  glViewport(0, 0, w, h);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  glTranslated(0.0, 0.0, -5.0);

}
void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col);

}
/*
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  
  glCullFace(GL_FRONT);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
  glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}
*/

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}
