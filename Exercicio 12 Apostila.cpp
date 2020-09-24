//Exercicio 12
#include <stdio.h>

float calculo(float x,float y,float z)
{
	float conta=x*y+z;
	return conta;
}

main()
{
	float a,b,c;
	scanf("%f %f %f",&a,&b,&c);
	printf("%0.2f",calculo(a,b,c));
}
