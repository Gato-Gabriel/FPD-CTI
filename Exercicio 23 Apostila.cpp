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
/* 23)	Faça um programa que peça para o usuário digitar um número
 inteiro em main maior que 0 (declare a var como global).
 Chame uma função que imprimirá na tela o símbolo $ (cifrão)
 na quantidade de linhas digitada na variável global, seguindo
 o padrão mostrado no exemplo. 
 Exemplo: se for digitado o número 4, a saída será:
$
$$
$$$
$$$$
*/
//bibliotecas
#include<stdio.h>

//variaveis globais
int cifrao;

//cabeçalho de funções
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

