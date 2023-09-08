#include<stdio.h>
#include<math.h>
#include <time.h>
int main(){
	double cpu_time;
	int hairetu[1000001];
	hairetu[0]=2;
	hairetu[1]=3;
	int n=3;
	int j;
	for(int i=0;i<1000000;n++){		//-----任意の回数回繰り返して任意の個数目の素数を持ってくる
		for(j=0; hairetu[j]<=sqrtf(n);j++){
			if(n%hairetu[j]==0){
				break;
			}
		}
		if(n%hairetu[j]!=0){
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
