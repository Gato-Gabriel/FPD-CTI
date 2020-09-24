//Exercicio 24 Apostila
#include <stdio.h>
void digita(float *w, float *x, float *y, float *z){
	printf("\nDigite a primeira nota:");
	scanf("%f",&*w);
	printf("Digite a segunda nota:");
	scanf("%f",&*x);
	printf("Digite a terceira nota:");
	scanf("%f",&*y);
	printf("Digite a quarta nota:");
	scanf("%f",&*z);
}
float media(float e, float f, float g, float h){
	float med=(e+f+g+h)/4;
	return med;
}
main(){
	float a,b,c,d;
	printf("Bo calcula umas media!");
	digita(&a,&b,&c,&d);
	float med=media(a,b,c,d);
	printf("\nO resultado da media eh: %0.1f",med);
}
