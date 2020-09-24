//Exercicio 11 Apostila
#include <stdio.h>
#include <conio.h>
#define pi 3.14159265
void area(float a)
{
	printf("A area da sua esfera eh: %0.6f\n",2*pi*a*a);
}
void volume(float v)
{
	printf("O volume da sua esfera eh: %0.6f\n",4./3.*pi*v*v*v);
}
main()
{
	float r;
	printf("Digite o valor do raio de sua esfera:");
	scanf("%f",&r);
	area(r);
	volume(r);	
}
