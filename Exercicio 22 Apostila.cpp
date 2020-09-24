//Exercicio 22 Apostila
#include <stdio.h>

int num;
void func();

main(){
	do{
	printf("Digite um numero maior que 0:");
	scanf("%d",&num);
	if (num<=0) printf("Errado!\n");
	}while (num<=0);
	func();
}

void func(){
	int n=1;
	for (n;n<=num;n++){
		for (int i=1;i<=5;i++){
		printf("@");
		}
		printf("\n");
	}
}

