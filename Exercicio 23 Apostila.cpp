#include <stdio.h>
int num;
void imprime();
main(){
	printf("Digite um numero maior que 0:");
	scanf("%d",&num);
	while(num<=0){
		printf("Valor errado. Redigite:");
		scanf("%d",&num);
	}
	imprime();
}

void imprime(){
	for (int i=1;i<=num;i++){
		printf("@@@@@\n");
	}
	printf("FIM :D !");
} 
/* 23)	Fa�a um programa que pe�a para o usu�rio digitar um n�mero
 inteiro em main maior que 0 (declare a var como global).
 Chame uma fun��o que imprimir� na tela o s�mbolo $ (cifr�o)
 na quantidade de linhas digitada na vari�vel global, seguindo
 o padr�o mostrado no exemplo. 
 Exemplo: se for digitado o n�mero 4, a sa�da ser�:
$
$$
$$$
$$$$
*/
//bibliotecas
#include<stdio.h>

//variaveis globais
int cifrao;

//cabe�alho de fun��es
void imprimir();

main()
{
	cifrao = 0;
	while(cifrao <= 0)
	{
		printf("\nDigite um valor (maior que 0): ");
		scanf("%d",&cifrao);	
		if(cifrao <= 0)
			printf("\nValor invalido, redigite! \n");	
	}
 	imprimir();
}
void imprimir()
{
	for(int i=1; i<=cifrao ; i++)
	{
		for(int j=1; j<=i; j++)
		{
			printf("$");	
		}
		printf("\n");	
	}
}

