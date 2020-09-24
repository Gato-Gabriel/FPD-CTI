//Exercicio 20 Apostila
#include <stdio.h>

int sum;
void soma(int,int);

main(){
	int num1,num2;
	printf("Digite o numero 1:");
	scanf("%d",&num1);
	printf("Digite o numero 2:");
	scanf("%d",&num2);
	soma(num1,num2);
	printf("A soma eh: %d",sum);
}

void soma(int n1, int n2){
	sum=n1+n2;
}
