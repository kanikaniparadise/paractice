#include <GL/glut.h>
#include <math.h>
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(0.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2d(1, -1);
  glVertex2d(3, -1);
  glVertex2d(2, (2*sin(M_PI/3))-1);
  glEnd();
  glFlush();
  
  glColor3d(1.0, 1.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2d(-1.0, -1.0);
  glVertex2d(1.0, -1.0);
  glVertex2d(1.0, 1.0);
  glVertex2d(-1, 1);
  glEnd();
  glFlush();
}
void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 変換行列の初期化 */
  glLoadIdentity();

  /* スクリーン上の表示領域をビューポートの大きさに比例させる */
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
  glutInitWindowSize(800, 240);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}
