#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
int *prime_list;
int i;

int sub(int n){	int j;
		for(j=0; prime_list[j]<=sqrtf(n);j++){
			if(n%prime_list[j]==0){
				break;
			}
		}
		if(n%prime_list[j]!=0){
			i++;
			prime_list[i]=n;
		}
}
int main(){
	double cpu_time;	
	prime_list = malloc(sizeof(int)*1000000);
	prime_list[0]=2;
	prime_list[1]=3;
	int n=3;
	
	for(i=0;i<1000000;n++){	
	sub(n);	//-----任意の回数回繰り返して任意の個数目の素数を持ってくる
		
	}
	cpu_time = clock();
	printf("%.2f", cpu_time/ CLOCKS_PER_SEC);
	float time1=time(NULL);
	printf("%f \n",time1);
	printf("%d",n-1);
	free(prime_list);
}
