#include<stdio.h>
int main(){
	int fb=1;
	int fbb=0;
	int f;
	for(int n=2;n<11;n++){
		f=fbb+fb;
		fbb=fb;
		fb=f;
		printf("%d \n",f);
	}
}
