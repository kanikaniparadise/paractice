#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
double point[35990][3];
int line[69470][3];

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
int numoff=0;
int numofv=0;

void display(void)
{
	
		printf("test");
	//  printf("%d\n",line);
		printf("test");
	glClear(GL_COLOR_BUFFER_BIT);

	//myGround(0.0);
	/* 図形の描画 */

	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	int i;
	for (i = 0; i < numoff; ++i) {
	  
	glVertex3dv(point[line[i][0]-1]);

	glVertex3dv(point[line[i][1]-1]);

	glVertex3dv(point[line[i][2]-1]);

	}
	printf("fin");
	glEnd();
	
	glFlush();
}
void resize(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(8, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void init(void)
{
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
		printf(" ");
		line[linenum][i]=num;
	      }
	      linenum++;
	      printf("%s\n","<line");
	    }
	  }
	  
	}
	fclose(fp); // ファイルを閉じる
	printf("%d\n",numoff);
	printf("test");

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
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
