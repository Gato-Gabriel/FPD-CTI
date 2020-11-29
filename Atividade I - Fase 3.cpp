#include <stdio.h>
#include <conio.h>
#include <conio.c>
#include <locale.h>
int valida(int);
void calculo(float, int);
float valor;
main(){
	setlocale(LC_ALL,"Portuguese");
	int tipo;
	float mens;
	textbackground(7); textcolor(3);
	printf("============================================================\n");
	printf("\tBem vindo ao menu da academia Coder!\t\t    \n");
	printf("============================================================");
	textbackground(0); textcolor(7);
	printf("\nDigite o valor inicial de sua mensalidade: R$ ");
	scanf("%f",&mens);
	printf("Que tipo de usu�rio voc� �?\n");
	textcolor(3);
	printf("\n[1] - Usu�rio Novato"); textcolor(6);
	printf("\n[2] - Usu�rio Intermedi�rio"); textcolor(12);
	printf("\n[3] - Usu�rio Veterano"); textcolor(7);
	printf("\n\nSua op��o: "); 
	scanf("%d",&tipo);
	tipo = valida(tipo);
	calculo(mens,tipo);
	textcolor(11);   printf("\n\tCalculando...\n"); 
	textcolor(7);	Sleep(2500);
	printf("\nO valor final de sua mensalidade ficar� em "); textcolor(2);
	printf("R$ %0.2f.",valor); textcolor(11);
	printf("\n\nObrigado por ter utilizado o menu da academia Coder. Volte sempre!"); textcolor(7);
}

int valida(int num){
	while (num<1 || num>3){
		textcolor(4);	printf("Tipo inv�lido. ");
		textcolor(7);   printf("Redigite por gentileza: "); 
		scanf("%d",&num);
	}
	return num;
}
	
void calculo(float mens, int tipo){
	switch (tipo){
		case 1: valor=1.1*mens; break;
		case 2: valor=1.15*mens; break;
		case 3: valor=1.2*mens; break;
	}
}
