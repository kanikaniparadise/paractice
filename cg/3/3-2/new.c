#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#define MAXPOINTS 100
int rubberband = 0;        /* ラバーバンドの消去 */
double vertex[35947][3];
int line[69451][3];
int numofv=0;
int numoff=0;
GLint point[MAXPOINTS][2];
float lookx;
float looky;
//視点関係//
double eye[3]={2,1,1};
double pov[3]={0,0,0};
double up[3]={0,1,0};
int x0;
int dx;














int pointnum = 0; 
#define W 6                        /* 地面の幅の２分の１　 */
#define D 9                        /* 地面の長さの２分の１ */
static void myGround(double height)
{
  const static GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  int i, j;

  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  for (j = -D; j < D; ++j) {
    for (i = -W; i < W; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, height, (GLdouble)j);
      glVertex3d((GLdouble)i, height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)j);
    }
  }
  glEnd();
}

double vertex2[][3]={
  {0,0,0},
  {2,0,0},
  {2,0,2},
  {0,0,2},
  {1,2,1}
};
int line2[][3]={
  {1,2,5},
  {2,3,5},
  {3,4,5},
  {4,1,5},
  {1,2,3},
  {1,3,4}
};

GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
int seeingx=1;





void display(void)
{


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





  
  const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


  
  
 
 
 
  //  printf("%d\n",line);
 
  glClear(GL_COLOR_BUFFER_BIT);
  //myGround(0.0);
  /* 図形の描画 */
 
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  int i;
  for (i = 0; i < numoff; ++i) {
    
    glVertex3dv(vertex[line[i][0]-1]);
    
    glVertex3dv(vertex[line[i][1]-1]);
    
    glVertex3dv(vertex[line[i][2]-1]);
    
  }
  printf("%s\n","fin");
  glEnd();
	
  glFlush();
}
void resize(int w, int h)
{
  glViewport(0, 0, w, h);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  glTranslated(0.0, 0.0, -5.0);
   gluLoookAt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],up[0],up[1],up[2]);
 
}



/*void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    lookx = -1;
    looky = 1;    
    gluLookAt(2, 2, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  }
}
*/
void motion(int x, int y){
  if(x0=0){
    dx=x0-x;
  }
  rot0(eye,up,dx,eye);
  gluLt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],up[0],up[1],up[2]);
  printf("%d\n",dx);
  glFlush();
}



void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[]) {









   glutInit(&argc, argv);
  glCullFace(GL_FRONT);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMotionFunc(motion);
  init();
  glutMainLoop();
  return 0;
}
