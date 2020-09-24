//Exercicio 10 Apostila
#include <stdio.h>
#include <conio.h>
void temp(float f)
{
	printf("A temperatura em Celsius eh: %0.2f",5./9.*(f-32));
}
main(){
	float num;
	printf("Digite uma temperatura em Fahrenheit:");
	scanf("%f",&num);
	temp(num);
}
