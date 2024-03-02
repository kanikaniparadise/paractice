#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#define MAXPOINTS 100
double vms[69500][3];
int vmnum=0;
double vertex[35947][3];
int face[69451][3];


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

GLfloat light0pos[] = { 0.0, 2.0, 5.0, 1.0 };
GLfloat light0col[] = { 0.5, 0.5, 0.5, 1.0 };












int pointnum = 0; 
#define W 6                        /* 地面の幅の２分の１　 */
#define D 9                        /* 地面の長さの２分の１ */

double vertex2[][3]={
  {0,0,0},
  {2,0,0},
  {2,0,2},
  {0,0,2},
  {1,2,1}
};
int face2[][3]={
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


  




  
  const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


  
  
 
 
 
  //  printf("%d\n",face);
 
  glClear(GL_COLOR_BUFFER_BIT);
  //myGround(0.0);
  /* 図形の描画 */
 
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  int i;
  for (i = 0; i < numoff; ++i) {
    //    glNormal3dv(vms[i]);
    
    glVertex3dv(vertex[face[i][0]-1]);
    
    glVertex3dv(vertex[face[i][1]-1]);
    
    glVertex3dv(vertex[face[i][2]-1]);
    
  }
  printf("%s\n","fin");
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



void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  FILE *fp; // FILE型構造体
  //char fname[] = "bunny.obj";
  char fname[] = "bunny.obj";
  
  char hed[10];

	
  int vertexnum=0;
  int facenum = 0;
	
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
      /*if(strcmp(hed,"vm")==0){
	for(int i=0;i<3;i++){
	  vmnum++;
	  //fscanf(fp,"%f",&num);
	  //vms[vmnum][i]=num;
	}
	printf("%d\n",vmnum);
      }
    
      else{*/
      if(strcmp(hed,"f")==0){
	  numoff++;
	  int i;
	  for(i=0;i<3;i++){
	    fscanf(fp,"%d",&fnum);
	    
	    //printf("%d",num);
	    //printf(" ");
	    face[facenum][i]=fnum;
	  }
	  facenum++;
	  //printf("%s\n","<face");
	}
    
  }
  
}
fclose(fp); // ファイルを閉じる

}
  
  int main(int argc, char *argv[]) {






  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);


   glutInit(&argc, argv);
  glCullFace(GL_FRONT);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();
  return 0;
}
