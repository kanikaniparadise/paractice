#include<stdio.h>
#include<math.h>
#include <time.h>
int main(){
	double cpu_time;
	int hairetu[1000000];
	hairetu[0]=1;
	hairetu[1]=2;
	int n=2;
	int yakusuu=0;
	for(int i=0;i<1000000;n++){
		yakusuu=0;
		for(int j=0; hairetu[j]<=sqrt(n)&&yakusuu<2;j++){
			if(n%hairetu[j]==0){
				yakusuu++;
			}	
		}
		if(yakusuu<2){
			i++;
			hairetu[i]=n;
		}
	}
	cpu_time = clock();
	printf("%.2f", cpu_time/ CLOCKS_PER_SEC);
	float time1=time(NULL);
	printf("%f \n",time1);
	printf("%d",n-1);
}
		
