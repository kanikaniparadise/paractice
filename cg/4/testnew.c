#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>


double vertex[35947][3];
int line[69451][3];
int numofv=0;
int numoff=0;


#define MAXPOINTS 100      /* 記憶する点の数　　 */
GLint point[MAXPOINTS][2]; /* 座標を記憶する配列 */
int pointnum = 0;          /* 記憶した座標の数　 */
int rubberband = 0;        /* ラバーバンドの消去 */

float lookx;
float looky;
//視点関係//
double eye[3]={7,3,1};
double pov[3]={0,0,0};
double up[3]={0,1,0};
int x0=0;
double dx=0;




void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  /* 記録したデータで線を描く 
  if (pointnum > 1) {
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (i = 0; i < pointnum; ++i) {
      glVertex2iv(point[i]);
    }
    glEnd();
    }*/

  glFlush();
}
void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 変換行列の初期化 */
  glLoadIdentity();

  /* スクリーン上の座標系をマウスの座標系に一致させる */
  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}



void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    /* ボタンを操作した位置を記録する */
    point[pointnum][0] = x;
    point[pointnum][1] = y;
    if (state == GLUT_UP) {
      /* ボタンを押した位置から離した位置まで線を引く */
      glColor3d(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2iv(point[pointnum - 1]); /* 一つ前は押した位置　 */
      glVertex2iv(point[pointnum]);     /* 今の位置は離した位置 */
      glEnd();
      glFlush();

      /* 始点ではラバーバンドを描いていないので消さない */
      rubberband = 0;
    }
    else {
    }
    if (pointnum < MAXPOINTS) ++pointnum;
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;
  default:
    break;
  }
}

void motion(int x, int y)
{
  static GLint savepoint[2]; /* 以前のラバーバンドの端点 */

  /* 論理演算機能 ON */
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_INVERT);

  glBegin(GL_LINES);
  if (rubberband) {
    /* 以前のラバーバンドを消す */
    glVertex2iv(point[pointnum - 1]);
    glVertex2iv(savepoint);
  }
  /* 新しいラバーバンドを描く */
  glVertex2iv(point[pointnum - 1]);
  glVertex2i(x, y);
  glEnd();

  glFlush();

  /* 論理演算機能 OFF */
  glLogicOp(GL_COPY);
  glDisable(GL_COLOR_LOGIC_OP);

  /* 今描いたラバーバンドの端点を保存 */
  savepoint[0] = x;
  savepoint[1] = y;
 
  /* 今描いたラバーバンドは次のタイミングで消す */
  rubberband = 1;
}





/*
void motion(int x, int y){
  int i;
 for(i=0;i<3;i++){
   printf("%f\n",eye[i]);
  }
  for(i=0;i<3;i++){
   printf("%f\n",pov[i]);
  }
  dx=(x0-x)/10;
  eye[0]+=dx;
  pov[0]+=dx;
  printf("%f\n",dx);
  //gluLookAt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],up[0],up[1],up[2]);
  glutPostRedisplay();
  glFlush();
  x0=x;
  
}
*/

//void idle(void){
//gluLookAt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],up[0],up[1],up[2]);
//glutPostRedisplay();
//}




void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
   FILE *fp; // FILE型構造体
  //char fname[] = "bunny.obj";
  char fname[] = "bunny.obj";
  
  char hed[10];

  
  int vertexnum=0;
  int linenum = 0;
	
  fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
  if(fp == NULL) {
    printf("%s file not open!\n", fname);
		
  }
  numoff=0;
  numofv=0;	
  while((fscanf(fp,"%s2",hed) != EOF)) {
    float num;
    int fnum;
    
    
    if(strcmp(hed,"v")==0){
      numofv++;
      int i;
      
      for(i=0;i<3;i++){
	fscanf(fp,"%f",&num);


	vertex[vertexnum][i]=num;
      }
      vertexnum=vertexnum+1;
    }
    else{
      if(strcmp(hed,"f")==0){
	numoff++;
	int i;
	for(i=0;i<3;i++){
	  fscanf(fp,"%d",&fnum);
		
	  //printf("%d",num);
	  //printf(" ");
	  line[linenum][i]=fnum;
	}
	linenum++;
	//printf("%s\n","<line");
      }
    }
    
    
  }
  fclose(fp); // ファイルを閉じる
 
}

int main(int argc, char *argv[]) {

  glutInitWindowPosition(100 , 50);
  glutInitWindowSize(400 , 300);






  glutInit(&argc, argv);
  glCullFace(GL_FRONT);
  

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutReshapeFunc(resize);
  //  glutIdleFunc(idle);
  init();
  glutMainLoop();
  return 0;
}
