//Exercício 26 Apostila
#include <stdio.h>
#include <conio.h>
#include <math.h>
void baskhara(int *a,int *b,int *c){
	int delta;
	delta=(*b * *b) - (4* *a * *c);
	printf("O delta eh: %d",delta);
	if (delta<0){
		printf("\nEquacao impossivel.");
	}
	else {	
		int x1=((- *b)+sqrt(delta))/2 * *a;
		int x2=((- *b)-sqrt(delta))/2 * *a;
		printf("\nX1 eh %d",x1);
		printf("\nX2 eh %d",x2);
	}
}
main(){
	int a,b,c;
	printf("Formula: ax^2 + bx + c");
	printf("\nDigite a:");	scanf("%d",&a);
	printf("\nDigite b:");	scanf("%d",&b);
	printf("\nDigite c:");	scanf("%d",&c);
	baskhara(&a,&b,&c);
}
