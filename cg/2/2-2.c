#include <stdlib.h>
#include <GL/glut.h>


static void display(void)
{

  /* 画面クリア */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();



  /* 視点の移動（物体の方を奥に移す）*/
  gluLookAt(4.0, 4.0, -4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* シーンの描画 */

  glutSolidTeapot(1.0);

  glFlush();
}
void resize(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  
}
void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}
