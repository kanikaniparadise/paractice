#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main(int argc,char **argv){
	int want = atoi(argv[1]);
	int n=2;
	int yakusuu=0;
	for(int i=0;i<want;n++){
		yakusuu=0;
		for(int j=1; j<=sqrt(n)&&yakusuu<2;j++){
			if(n%j==0){
				yakusuu++;
				
			}	
		}
		if(yakusuu<2){
			i++;

		}
	}
	printf("%d",n-1);
}
		
