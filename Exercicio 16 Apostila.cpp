//Exercicio 16 Apostila
#include <stdio.h>
float media(float a, float b, float c, float d)
{
	return (a+b+c+d)/4;
}
main()
{
	float a,b,c,d;
	printf("Digite os valores em ordem:");
	scanf("%f %f %f %f",&a,&b,&c,&d);
	float calculo=media(a,b,c,d);
	printf("A sua media eh: %0.1f",calculo);
}
