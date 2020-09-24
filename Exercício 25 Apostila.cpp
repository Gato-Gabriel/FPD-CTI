//Exercício 25 Apostila
#include <stdio.h>
#include <locale.h>
void inverte(int *a,int *b){
	int aa=*a;
	*a=*b;
	*b=aa;
}
main(){
	setlocale(LC_ALL,"Portuguese");
	int a,b;
	printf("Digite o valor de a: ");	scanf("%d",&a);
	printf("Digite o valor de b: ");	scanf("%d",&b);
	printf("Valor de a e b antes da função: %d e %d.",a,b);
	inverte(&a,&b);
	printf("\nValor de a e b após a função: %d e %d.",a,b);
}
