#include <stdio.h>
int main(){
	for (int i=1; i<21; i++){
		printf("\n");
		printf("%d",i);
		if(i%3==0){
			printf("foo");
		}
		if(i%5==0){
			printf("bar");
		}
	}
}
