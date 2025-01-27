#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
double point[35947][3];
int line[69451][3];
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

double point2[][3]={
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


void display(void)
{
  int numofv=0;
  int numoff=0;
  const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


  
	FILE *fp; // FILE型構造体
	char fname[] = "piramid.obj";
	char hed[10];

	
	int pointnum=0;
	int linenum = 0;
	
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		
	}
	
	while((fscanf(fp,"%s2",hed) != EOF)) {
	  int num;


	  if(strcmp(hed,"v")==0){
	    numofv++;
	    int i;
	    printf("b");
	    for(i=0;i<3;i++){
	      fscanf(fp,"%d",&num);

	      point[pointnum][i]=num;
	    }
	    pointnum=pointnum+1;
	  }
	  else{
	    if(strcmp(hed,"f")==0){
	      numoff++;
	      int i;
	      for(i=0;i<3;i++){
		fscanf(fp,"%d",&num);

		printf("%d",num);
		line[linenum][i]=num;
	      }
	      linenum++;
	      printf("%s\n","<line");
	    }
	  }
	  
	}
	fclose(fp); // ファイルを閉じる
	int i;
	for(i=0;i<5;i++){
	  printf("\n%f",point[i][0]);
	printf("\n%f",point[i][1]);
	printf("\n%f",point[i][2]);
	}
	for(i=0;i<10;i++){
	  printf("\n%d",line[i][0]);
	  printf("\n%d",line[i][1]);
	  printf("\n%d",line[i][2]);
	}

  //  printf("%d\n",line);

  glClear(GL_COLOR_BUFFER_BIT);
  //myGround(0.0);
  /* 図形の描画 */
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < numoff; ++i) {

  glVertex3dv(point[line[i][0]-1]);
  printf("%f",  *point2[line2[i][0]-1]);
  glVertex3dv(point[line[i][1]-1]);
    printf("%f",  *point2[line2[i][1]-1]);
  glVertex3dv(point[line[i][2]-1]);
    printf("%f\n",  *point2[line2[i][2]]-1);
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
  gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	init();
	glutMainLoop();
	return 0;
}
