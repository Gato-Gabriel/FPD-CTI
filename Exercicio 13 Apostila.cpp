//Exercicio 13
#include <stdio.h>
#include <conio.h>
float tensao(float r,float c)
{
	float t=r*c;
	return t;
}
main()
{
	float resist;
	float corrente;
	printf("Digite o valor da resistencia:");
	scanf("%f",&resist);
	printf("Digite o valor da corrente:");
	scanf("%f",&corrente);
	tensao(resist,corrente);
	if(tensao(resist,corrente)<0)
	do{
		printf("Digite novamente.\n");
		printf("Digite o valor da resistencia:");
		scanf("%f",&resist);
		printf("Digite o valor da corrente:");
		scanf("%f",&corrente);
		tensao(resist,corrente);
	}while(tensao(resist,corrente)<0);
	printf("A tensao eletrica eh de %.2f volts",tensao(resist,corrente));
}
