#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

GLfloat light0pos[] = { 0.0, 5.0, -10.0, 1.0 };
GLfloat light0col[] = { 0.2, 0.2, 0.2, 1.0 };
GLdouble ns[69451][3];

double vertex[35947][3];
int line[69451][3];

int numofn=0;
int numofv=0;
int numoff=0;

//視点関係//
int x0;
int dx;



#define W 6                        /* 地面の幅の２分の１　 */
#define D 9                        /* 地面の長さの２分の１ */

double bectlong(double *a){
  double ans=0;
  for(int i=0;i<3;i++){
    ans += a[i]*a[i];
  }
  ans=sqrt(ans);
  return ans;
}
void bectnormal(double *a,double *ans ){
  double longer;
  longer = bectlong(a);
  for(int i=0;i<3;i++){
    ans[i]=(a[i]/longer);
  }
  
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


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  gluLookAt(0 , 5, -10, 0.0, 0, 0.0, 0.0, 1.0, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos); 
  //  printf("%d\n",line);
 
  /* 図形の描画 */
 


  glBegin(GL_TRIANGLES);
  int i;
  for (i = 0; i <numoff; i++) {
    double norm[3];
    for(int j=0;j<3;j++){
	printf("%f\n",ns[i][j]);
      }
    double aaaaaa[3] ={0,1,0};
    glNormal3dv(ns[i]);
    
    glVertex3dv(vertex[line[i][0]-1]);
    
    glVertex3dv(vertex[line[i][1]-1]);
    
    glVertex3dv(vertex[line[i][2]-1]);
    
  }
  printf("%s\n","fin");
  glEnd();
glutSwapBuffers();

}

void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 変換行列の初期化 */
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);


}




void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  FILE *fp; // FILE型構造体

  char fname[] = "bunny.obj";
  
  char hed[100];

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
  
  


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
      printf("\n%s",hed);
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
      else{
	if(strcmp(hed,"vn")==0){
	    printf("vn");
	    for(int i=0;i<3;i++){
	      fscanf(fp,"%f",&num);
	      ns[numofn][i]=num;
	    }
	    numofn++;
	}	
      }
    }
    
    
  }
  fclose(fp); // ファイルを閉じる
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col);


}

int main(int argc, char *argv[]) {



  

  glutInit(&argc, argv);
  glCullFace(GL_FRONT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();
  return 0;
}
