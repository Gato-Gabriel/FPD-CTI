//Exercicio 9 Apostila
#include <stdio.h>
#include <conio.h>

void tab(int a, int b, int c)
{
	for (b=1;b<=10;b++)
	{
		printf(" %d X %d = %d\n",a,b,a*b);
	}
}
main()
{
	int x,y,z;
	scanf ("%d",&x);
	tab(x,y,z);
}
