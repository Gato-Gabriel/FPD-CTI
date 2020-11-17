//Exercício 32
#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <string.h>
#include <conio.c>
#define max 5
using namespace std;

struct dados{
	char codigo[10],nome[30],especie[15],raca[30];
	float valor;
	int dia,mes,ano;
};

void leitura(dados base[max]){
	for(int i=0;i<max;i++){
		cout << "\n\t====Animal "<< i+1 << " ====\n";		fflush(stdin);
		cout << " Digite o código de seu animal: ";	  gets(base[i].codigo);		fflush(stdin);
		cout << " Digite o nome do animal: ";	 gets(base[i].nome);		fflush(stdin);
		cout<<" Digite a data de aniversario dele(dia/mes/ano):   /  /";
		gotoxy(50,5);	cin>>base[i].dia;	
		gotoxy(53,5);	cin>>base[i].mes;   
		gotoxy(56,5);	cin>>base[i].ano;
		fflush(stdin);
		cout << " Digite a espécie do animal: ";	 gets(base[i].especie);	 fflush(stdin);
		cout << " Digite a raça do animal: ";	 gets(base[i].raca);		fflush(stdin);
		cout << " Digite o valor do animal: R$ ";	 cin>>base[i].valor;
		system("cls");
	}
}

void mostra(dados nova){
	cout << " Codigo: ";	puts(nova.codigo);
	cout << " Nome: ";	puts(nova.nome);
	printf(" Data de aniversario: %d/%d/%d \n",nova.dia,nova.mes,nova.ano);
	cout << " Espécie: " <<  nova.especie;
	cout << "\n Raça: " << nova.raca;
	cout << "\n Valor: R$ " << nova.valor;
}

int main(){
	setlocale(LC_ALL,"Portuguese");
	dados vet[max];
	textbackground(9);		gotoxy(16,2);
	cout << "Clínica Veterinária - Cadastros";
	textbackground(0);	 Sleep(2000);	 system("cls");
	leitura(vet);
	textcolor(CYAN);
	cout << "\t Exibindo dados...\n";	Sleep(1000);
	textcolor(WHITE);
	for(int j=0;j<max;j++){
		cout << "\n\t====Animal "<<j+1<<" ====\n";
		mostra(vet[j]);
	}
	return 0;
}
