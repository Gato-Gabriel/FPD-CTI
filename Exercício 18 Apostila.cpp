#include <stdio.h>
 int pot(int a, int b){
 	int i=1;
 	int c = a;
 	while (i<b){
 		c*=a;
 		i++;
	 }
	 return c;
 }
 main(){
 	int num, expo;
 	printf("Bo potencia uns bagui ai; ");
 	printf("Digite o numero:");
 	scanf("%d",&num);
 	printf("Digite o expoente: ");
 	scanf("%d",&expo);
 	int powe = pot(num, expo);
 	printf("%d elevado a %d eh %d.",num,expo,powe);
 }
