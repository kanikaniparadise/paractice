#include <stdlib.h>
#include <stdio.h>
int main(){
  FILE *fp;
  char i[8];
  char fname[]="piramid.obj";
  fp = fopen(fname,"r");
  fscanf(fp,"%s",i);
  char chr[256];
  printf("%s",i);
  if(i=="v"){
    fgets(chr,256,fp);
    printf("%s",chr);

  }
      
  fclose(fp);
}
