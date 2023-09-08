#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
int main(){
	double cpu_time;
	int *prime_list;
	prime_list = malloc(sizeof(int)*1000000);
	prime_list[0]=2;
	prime_list[1]=3;
	int n=3;
	int j;
	int sqn;
	int flag;
	for(int i=1;i<1000000;n+=2){		//-----任意の回数回繰り返して任意の個数目の素数を持ってくる
		
		sqn=sqrtf(n);
		for(j=0; prime_list[j]<=sqn;j++){
			if(n%prime_list[j]==0){
				break;
			
			}
		}
		if(n%prime_list[j]!=0){
			prime_list[i]=n;
			i++;
			
		}
	}
	cpu_time = clock();
	printf("%.2f", cpu_time/ CLOCKS_PER_SEC);
	float time1=time(NULL);
	printf("%f \n",time1);
	printf("%d",n-2);
	free(prime_list);
}
