//Exercicio 15
#include <stdio.h>
int valida(int aa)
{
	if(aa<0 || aa>10)
	{
		do{
			printf("Errado!Redigite por favor:");
			scanf("%d",&aa);
		}while(aa<0 || aa>10);
	}
	else
	return aa;
}
main()
{
	int a;
	printf("Digite um numero entre 0 e 10:");
	scanf("%d",&a);
	valida(a);
	printf("Voce acertou! %d",a);
}
