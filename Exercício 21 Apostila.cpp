//Exercicio 21 Apostila
#include <stdio.h>

int num;

void chama();

main(){
	do{
	printf("Digite um numero maior que 2:");
	scanf("%d",&num);
	if(num<=2) printf("Errado!\n");
	}while(num<=2);
	chama();
}

void chama(){
	int n=1;
	for (n;num>=n;n++){
		printf("%d\n",n);
	}
}
