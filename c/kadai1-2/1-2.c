#include <stdio.h>
int main(){
	for (int i=1; i<31; i++){
		printf("\n");
		printf("%d",i);
		if(i%3==0){
			printf(" foo");
		}
		if(i%5==0){
			printf(" bar");
		}
		if(i%7==0){
			printf(" hoge");
		}
		if(i%11==0){
			printf(" piyo");
		}
		
	}
	printf("\n");
}
