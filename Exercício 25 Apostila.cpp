//Exerc�cio 25 Apostila
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
	printf("Valor de a e b antes da fun��o: %d e %d.",a,b);
	inverte(&a,&b);
	printf("\nValor de a e b ap�s a fun��o: %d e %d.",a,b);
}
