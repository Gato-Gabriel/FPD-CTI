//Exercicio 14
#include <stdio.h>
#include <conio.h>
float imc(float p, float a)
{
	float cal=p/(a*a);
	return cal;
}
main()
{
	float peso, altura;
	printf("Vamos calcular o seu IMC!");
	printf("Digite seu peso (em kg):");
	scanf("%f",&peso);
	printf("Digite sua altura (em m):");
	scanf("%f",&altura);
	imc(peso,altura);
	float IMC=imc(peso,altura);
	printf("O seu IMC eh: %0.2f",IMC);
	if (IMC<=18.5)
	printf("\nAbaixo do peso");
	else if(IMC>=18.6 && IMC<=24.9)
	printf("\nPeso normal");
	else if(IMC>=25 && IMC<=29.9)
	printf("\nSobrepeso/pré-obesidade");
	else if(IMC>=30 && IMC<=34.9)
	printf("\nObesidade grau I");
	else if(IMC>=35 && IMC<=39.9)
	printf("\nObesidade grau II");
	else if(IMC>=40)
	printf("\nObesidade grau III");
}
