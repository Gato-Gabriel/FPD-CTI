//nuevo teste para prueba
#include <stdio.h>
#include <conio.h>
float calculo(float r,float i)
{
		if(r<0 || i<0)
		{
		printf("Um dos valores esta negativo. Nao foi possivel calcular");
		return 0;}
	float u=r*i;
	printf("A tensao eh: %0.2f",u);
}
main()
{
	float res,cor;
	printf("Vamos calcular a tensao de um sistema!\n Digite a resistencia:");
	scanf("%f",&res);
	printf("Digite a corrente:");
	scanf("%f",&cor);
	calculo(res,cor);
}
