#include <GL/glut.h>

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

int edge[][4] = {
  { 0, 1 ,2,3},//正面
  {4,5,6,7  },//奥
  { 0,1,5,4 },//下
  {2,3,7,6 },//上
  {1,2,6,5  },//右側面
  { 0,3,4,7 }//左側面
};

double bect[][3]={
  {0,0,-1},
  {0,0,1},
  {0,-1,0},
  {0,1,0},
  {1,0,0},
  {-1,0,0}
};
  

float eye[4]={2,2,-2,1};



GLfloat mater[] = { 1, 1,1 , 0.3 };
GLfloat green[] = { 1.0, 2.0, 1.0, 1.0 };

void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);



  /* 視点の移動（物体の方を奥に移す）*/


  /* 図形の描画 */

  glBegin(GL_QUADS);
  for (i = 5; i < 6; ++i) {
    glNormal3dv(bect[i]);
    glVertex3dv(vertex[edge[i][0]]);
    glVertex3dv(vertex[edge[i][1]]);
    glVertex3dv(vertex[edge[i][2]]);
    glVertex3dv(vertex[edge[i][3]]);
  }
  glEnd();

  glFlush();
}
void resize(int w, int h)
{
  glViewport(0, 0, w, h);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  glTranslated(0.0, 0.0, -5.0);
  gluLookAt(2,2,-2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void init(void)
{
  glClearColor(1.0, 0.0, 0.0, 1.0);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
  //glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
  //glLightfv(GL_LIGHT1, GL_SPECULAR, green);
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
