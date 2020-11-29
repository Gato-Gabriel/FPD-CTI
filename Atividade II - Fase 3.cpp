/*  Trabalho - FPD
	Gabriel Gato Piragini Sant'Ana		n 07		71A
*/
#include <stdio.h>
#include <locale.h>
#include <conio.c>
#define verde textcolor(2);
#define txtnormal textcolor(7);
#define azulclaro textcolor(9);
#define azulesc textcolor(1);
#define amarelo textcolor(6);
void leia(int *,float *);
void calculo(int ,float);
main(){
	setlocale(LC_ALL,"Portuguese");
	int horas;
	float valor_hora;
	textbackground(7);	textcolor(1);
	printf("\n\t--//--//--//--CÁLCULO SALARIAL--//--//--//--\t\t\n\n");	txtnormal
	textbackground(0);
	leia(&horas,&valor_hora);
	calculo(horas, valor_hora);
}
void leia(int *horas,float *valor){
	printf("Digite o número total de horas que você trabalha por semana: ");	azulclaro	scanf("%d",&*horas);
	txtnormal
	printf("Digite o valor de cada hora trabalhada: ");	 	verde	
	printf("R$ ");	scanf("%f",&*valor);
	txtnormal
}
void calculo(int horas, float valor){
	float salario;
	int excedente = horas-40;
	if (horas>40 && horas<=60){
		salario = ( 40 * valor + excedente* (valor * 1.5));
	}
	else if (horas>60){
		int exc=horas-60;
		salario = ( 40 * valor + (excedente-exc) * (valor * 1.5) + exc * (valor * 2));
	}
	else{
		salario= horas * valor;
	}
	azulclaro	printf("\n\tCalculando dados...\n");	Sleep(2000);
	txtnormal
	printf("\nTotal de horas trabalhadas: ");	azulclaro	printf("%d", horas);
	txtnormal
	printf("\nQuantidades de horas excedentes: ");		amarelo
	if (excedente<=0){
		printf("Não há horas excedentes.");
	}
	else{
		printf("%d",excedente);
	}
	txtnormal
	printf("\nValor da hora trabalhada: ");		verde 	 printf("R$ %.2f",valor);
	txtnormal
	printf("\nSalário semanal: ");	verde 	printf("R$ %.2f",salario);
	txtnormal
}
