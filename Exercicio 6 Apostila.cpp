//Exercicio 6 Apostila
#include <stdio.h>
#include <conio.h>

void cube(float x)
{
	float cubo=x*x*x;
	printf("O cubo do seu numero eh: %.2f",cubo);
}
main()
{
	float num;
	printf("Digite o numero o qual voce deseja elevar ao cubo:");
	scanf("%f",&num);
	cube(num);
}
