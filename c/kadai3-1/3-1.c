#include<stdio.h>
#include<math.h>
int main(){
	int n=2;
	int yakusuu=0;
	for(int i=0;i<10;n++){
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
		
