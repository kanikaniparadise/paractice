#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

double vertex[35947][3];
int line[69451][3];
int numofv=0;
int numoff=0;

float lookx;
float looky;
//視点関係//
double eye[3]={0,0,7};
double pov[3]={0,0,0};
double up[3]={0,1,0};
double xb=0;
double dx=0;
double yb=0;
double dy=0;
int mousetype;
double fovh=30;
double fovv;



typedef struct{
  double a;
  double b;//i成分
  double c;//j成分
  double d;//k成分
} Qua;

void showq(Qua v){
  printf("%+8.3f    %+8.3f %+8.3f %+8.3f \n",v.a,v.b,v.c,v.d);
}

Qua qua_add(Qua q1,Qua q2){
  Qua ret;
  ret.a = q1.a + q2.a;
  ret.b = q1.b + q2.b;
  ret.c = q1.c + q2.c;
  ret.d = q1.d + q2.d;
  return ret;
}
Qua bar(Qua q){
  Qua ret;
  ret.a =  q.a;
  ret.b = -q.b;
  ret.c = -q.c;
  ret.d = -q.d;
  return ret;
}
Qua qua_mul(Qua q1,Qua q2){
  Qua ret;
  double a1=q1.a;     double a2=q2.a;
  double b1=q1.b;     double b2=q2.b;
  double c1=q1.c;     double c2=q2.c;
  double d1=q1.d;     double d2=q2.d;
  ret.a = a1*a2 - b1*b2 - c1*c2 - d1*d2;// 1成分
  ret.b = b1*a2 + a1*b2 - d1*c2 + c1*d2;// i成分
  ret.c = c1*a2 + d1*b2 + a1*c2 - b1*d2;// j成分
  ret.d = d1*a2 - c1*b2 + b1*c2 + a1*d2;// k成分
  return ret;  
}
double norm(Qua q){
  double a=q.a;
  double b=q.b;
  double c=q.c;
  double d=q.d;
  return sqrt(a*a+b*b+c*c+d*d);
}
Qua normalize(Qua q){
  double n = norm(q);
  if(n<1e-10){ puts("Error: normalize()  norm is almost 0"); exit(-1); }
  double inv = 1.0/n;
  q.a *= inv;    q.b *= inv;    q.c *= inv;    q.d *= inv;
  return q;
}
Qua getq(double rad, Qua u){
  Qua ret;
  ret.a = cos(rad/2);
  ret.b = sin(rad/2)*u.b;
  ret.c = sin(rad/2)*u.c;
  ret.d = sin(rad/2)*u.d;
  return ret;
}

//原点を通る任意軸回転
void rot0(double *p0, double *axis, double rad, double *p1){// u:回転軸の方向ベクタ
  Qua u,src;
  u.a  =0;   u.b  =axis[0]; u.c  =axis[1]; u.d  =axis[2];
  src.a=0;   src.b=p0[0];   src.c=p0[1];   src.d=p0[2];
  u = normalize(u);
  Qua q   = getq(rad,u);
  Qua qa  = qua_mul(q,src);
  Qua dst = qua_mul(qa,bar(q));
  p1[0]=dst.b;
  p1[1]=dst.c;
  p1[2]=dst.d;
}

//任意軸回転
void rot(double *p0, double *axis, double *ofs, double rad, double *p1){
  // ofsを原点に並行移動してから回転し、その後にもどす
  double org[3];    org[0]=p0[0];    org[1]=p0[1];     org[2]=p0[2]; 
  //平行移動（往路）
  org[0]-=ofs[0];   org[1]-=ofs[1];   org[2]-=ofs[2];
  //原点を通る軸で回転
  rot0(org,axis,rad, p1);
  //平行移動（復路）
  p1[0]+=ofs[0];    p1[1]+=ofs[1];    p1[2]+=ofs[2];
}









int pointnum = 0; 
#define W 6                        /* 地面の幅の２分の１　 */
#define D 9                        /* 地面の長さの２分の１ */
double www=400;
double hhh=300;

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

//ベクトル計算
void bectsum(double *a, double *b,double *ans){
  for(int i=0;i<3;i++){
    ans[i]= a[i]+b[i];
  }

}
void bectminus(double *a, double *b,double *ans){
  for(int i=0;i<3;i++){
    ans[i]= a[i]-b[i];
  }

}

void bectscalar(double *a, double b,double *ans){
  for(int i=0;i<3;i++){
    ans[i]= a[i]*b;
  }
}
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
  printf("%f\n",longer);
  for(int i=0;i<3;i++){
    ans[i]=(a[i]/longer);
  }
  
}
double bectnaiseki(double *a,double *b){
  double  ans=0;
  for(int i=0;i<3;i++){
    ans += a[i]*b[i];
  }
  return ans;
}
void bectgaiseki(double *a,double *b,double *ans ){
  int longer;
  longer=(bectlong(a));
  ans[0]=(a[1] * b[2])-(a[2] * b[1]);
  ans[1]=(a[2] * b[0])-(a[0] * b[2]);
  ans[2]=(a[0] * b[1])-(a[1] * b[0]);
}
void bectuetoru(double *a,double *ans){
  double subans[3];
  subans[1]=0;
  subans[0]=a[0];
  subans[2]=a[2];

  printf("%f\n",ans[1]);
  if(a[0]==0){
    ans[2]=(-1) * a[1];
    ans[0]=0;
  }else{
    if(a[2]==0){
      printf("%f\n",a[1]);
      ans[0]=(-1) * a[1];
      ans[2]=0;
      printf("koko");
    }else{
      ans[0]=(-1) * a[1] * (subans[0]/(subans[0]+subans[2]));
      ans[2]=(-1) * a[1] * (subans[2]/(subans[0]+subans[2]));
    }
  }
  ans[1]=bectlong(subans);
}
//ベクトル計算ここまで








void display(void)
{
  
  double hikisuu1[3]={1,2,0};
  bectuetoru(hikisuu1,hikisuu1);
  for(int i =0;i<3;i++){
    printf("%f\n",hikisuu1[i]);
  }
  
  printf("%s\n","startdisp");
  //  printf("%d\n",line);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  
  gluPerspective(fovh,www /hhh, 1.0, 100.0);
  gluLookAt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],0,1,0);
 

  //myGround(0.0);
  /* 図形の描画 */
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  int i;
  for (i = 0; i < numoff; ++i) {
    
    glVertex3dv(vertex[line[i][0]-1]);
    
    glVertex3dv(vertex[line[i][1]-1]);
    
    glVertex3dv(vertex[line[i][2]-1]);
    
  }
  //
  glEnd();

  glBegin(GL_LINES);
  glColor3d(1,0,0);
  glVertex3d(-3,0,0);
  glVertex3d(  3,0,0);
  glColor3d(0,1,0);
  glVertex3d(0,-3,0);
  glVertex3d(0,3,0);
  glColor3d(0,0,1);
  glVertex3d(0,0,-3);
  glVertex3d(0,0,3);
  glEnd();

  
  glBegin(GL_LINES);
  glColor3d(1,0,0);
  glVertex3d((pov[0]-3),pov[1],pov[2]);
  glVertex3d((pov[0]+3),pov[1],pov[2]);
  glColor3d(0,1,0);
  glVertex3d(pov[0],(pov[1]-3),pov[2]);
  glVertex3d(pov[0],(pov[1]+3),pov[2]);
  glColor3d(0,0,1);
  glVertex3d(pov[0],pov[1],(pov[2]-3));
  glVertex3d(pov[0],pov[1],(pov[2]+3));
  glEnd();
  glFlush();
  printf("%s\n","findisp");

}
void resize(int w, int h)
{


  www=w;
  hhh=h;
  glViewport(0, 0, w, h);


  


 
}



void mouse(int button, int state, int x, int y)
{
  yb=y;
  xb=x;
  switch (button) {
  case GLUT_LEFT_BUTTON:
    mousetype=0;
    break;
  case GLUT_RIGHT_BUTTON:
    mousetype=1;
    break;
  case GLUT_MIDDLE_BUTTON:
    mousetype=2;
    break;
  }
}



double xjiku[3]={1,0,0};
void motion(int x, int y){
  double radxz;
  double radxy;
  double ue[3] = {0,1,0};
  double ep[3]={
    eye[0]-pov[0],
    eye[1]-pov[1],
    eye[2]-pov[2]	
  };
  //  radxz=atan2(ep[2],ep[0]);
  //radxy=atan2(ep[1],ep[0]);
  radxz=radxz*(-1);
  dy=yb-y;
  dx=xb-x;
  if(mousetype==0){
    int i;
    printf("%s\n","start");

    double eyebect[3];
    
    bectnormal(ep,eyebect);
    bectuetoru(eyebect,up);
    double  kaitenx=(dx*180/(1000*6.28));
    double  kaiteny=(dy*180/(1000*6.28));
    for(i=0;i<3;i++){
      printf("%f\n",eyebect[i]);
    }
    rot0(eye,ue,kaitenx,eye);

    bectgaiseki(eyebect,up,xjiku);
    rot0(eye,xjiku,kaiteny,eye);
    printf("%s\n","kokoa");
    
  
    glutPostRedisplay();
  }
  else{
    if(mousetype==1){
      double xmove[3];
      double ymove[3];
      double summove[3];
      bectscalar(xjiku,(dx/100),xmove);
      bectscalar(up,(dy/100),ymove);
      bectsum(xmove,ymove,summove);
      bectsum(eye,summove,eye);
      bectsum(pov,summove,pov);
      /*
      printf("%f\n",dx);
      dx=-1*(xb-x)/100;
      dy=1*(yb-y)/100;
      eye[1]+=((dy)*cos(radxy));
      pov[1]+=((dy)*cos(radxy));
      eye[0]+=cos(atan2(ep[1],ep[2]))*(dy*sin(radxy));
      eye[0]+=(dx*sin(radxz));
      pov[0]+=(dx*sin(radxz));
      
      eye[2]+=(dx*cos(radxz));
      pov[2]+=(dx*cos(radxz));
      printf("%f\n",dx);
      //gluLookAt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],up[0],up[1],up[2]);
      */
      glutPostRedisplay();
    }else {
      if(mousetype==2){
	fovh+=(dy/10);
	fovv=fovh*(www/hhh);
	glutPostRedisplay();
	  
      }
    }
  }
  xb=x;
  yb=y;
  
}


//void idle(void){
//gluLookAt(eye[0],eye[1],eye[2],pov[0],pov[1],pov[2],up[0],up[1],up[2]);
//glutPostRedisplay();
//}




void init(void)
{
  
  glClearColor(1.0, 1.0, 1.0, 1.0);
  FILE *fp;
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
