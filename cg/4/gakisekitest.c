#include <stdio.h>
int main(){
  
void bectgaiseki(double *a,double *b,double *ans ){
  ans[0]=(a[1] * b[2])-(a[2] * b[1]);
  ans[1]=(a[2] * b[0])-(a[0] * b[2]);
  ans[2]=(a[0] * b[1])-(a[1] * b[0]);
}
 double a[3]={1,0,0};
 double b[3]={0,1,0};
 double c[3]; double d[3];
 bectgaiseki(a,b,c);
 for(int i;i<3;i++){
   printf("%f\n",c[i]);
 }
 bectgaiseki(a,c,d);

 if(d[1]<0){
   for(int i;i<3;i++){
     d[i]=d[i]*(-1);
   }
 }
 for(int i;i<3;i++){
   printf("%f\n",d[i]);
 }
}
