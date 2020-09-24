//Exercicio 17 Apostila
#include <stdio.h>
int fatorial(int a)
{
	int i=a-1;
	do{
		a*=i;
		i--;
	}while(i>=1);
}
main()
{
	int a;
	printf("Fala negao fala Dinho:");
	scanf("%d",&a);
	int c=fatorial(a);
	printf("O fatorial eh: %d",c);
}
