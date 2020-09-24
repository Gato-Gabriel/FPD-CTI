//Exercicio 27 Apostila
#include <stdio.h>
void fatorial(int *a){
	for (*a;*a>=1;*a--){
		printf("\n%d",*a);
	}
}
main(){
	int num;
	printf("Bo calcula uns fatorial, fi!");
	printf("\nDigite o numero: ");
	scanf("%d",&num);
	fatorial(&num);
	printf("\nO fatorial eh %d",num);
}
