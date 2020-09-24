//Exercicio 8 Apostila
#include <stdio.h>
#include <conio.h>
void det(int x)
{	if(x>0)
	printf("E positivo");
	else if(x<0)
	printf("E negativo");
	else
	printf("E nulo");}
main()
{	int a;
	printf("Digite um numero:");
	scanf("%d",&a);
	det(a);}
