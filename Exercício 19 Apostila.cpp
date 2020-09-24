#include <stdio.h>
float med;
void media(float,float,float,float);

main(){
	float n1,n2,n3,n4;
	printf("Digite a nota 1: ");
	scanf("%f",&n1);
	printf("Digite a nota 2: ");
	scanf("%f",&n2);
	printf("Digite a nota 3: ");
	scanf("%f",&n3);
	printf("Digite a nota 4: ");
	scanf("%f",&n4);
	media(n1,n2,n3,n4);
	printf("A media eh %0.2f",med);
}

void media(float a,float b,float c,float d){
	med=(a+b+c+d)/4;
}
