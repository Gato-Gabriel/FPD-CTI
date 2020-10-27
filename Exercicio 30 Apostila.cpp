#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include <conio.c>
#include <conio.h>
#define limpa fflush(stdin);
using namespace std;

struct cadastro{
	char nome[50];
	char cidade[25];
	int CEP;
	char telefone[15];
	char email[40];
	int dia_a;
	int mes_a;
	int ano_a;
};
void mostra(cadastro);
main(){
	setlocale(LC_ALL,"Portuguese");
	cadastro vet[3];
	char confirma[5];
	printf(" Bem vindo ao menu de cadastros!!!\n");
	printf(" Vamos cadastra-lo no cartao Lojas Guanabara!!!\n");
	for(int c=0;c<=20;c++)
		cout<"=";
	for(int i=0;i<3;i++){
		do{
			cout << "\n ==Cadastro numero " << i+1 << " ==\n";
			cout << "Por gentileza, digite seu nome:";	gets(vet[i].nome);	  limpa
			cout << "Digite sua cidade:";	gets(vet[i].cidade);	limpa
			cout << "Digite seu CEP: ";		cin>>vet[i].CEP;	 limpa
			cout << "Digite seu e-mail: ";	gets(vet[i].email);		limpa
			cout << "Digite seu telefone: ";	gets(vet[i].telefone);	 limpa
			cout << "Digite sua data de nascimento(dia/mes/ano): ";		scanf("%d",&vet[i].dia_a);
			cout << "/";	scanf("%d",&vet[i].mes_a);	cout << "/";	scanf("%d",&vet[i].ano_a);
			cout << "Deseja confirmar os dados? ";
			cin >> confirma;	strlwr(confirma);
		}while(strstr("sim",confirma)==0);
		textcolor(GREEN);	cout << "\n Dados salvos!!\n";	textcolor(LIGHTGRAY);
		fflush(stdin);
	}
	system("cls");		textcolor(WHITE);
	for(int j=0;j<3;j++){
		cout << "\n\tDados do cadastro " << j+1 << " :\n";
		mostra(vet[j]);
	}
}
void mostra(cadastro dados){
	cout << " Seu nome eh: ";	puts(dados.nome);
	cout << " Sua cidade eh " << dados.cidade;
	cout << "\n Seu CEP eh " << dados.CEP;
	cout << "\n Seu email para contato e: " << dados.email;
	cout << "\n Seu telefone para contato e: " << dados.telefone;
	cout << "\n Voce nasceu em " << dados.dia_a << "/" << dados.mes_a << "/" << dados.ano_a << "\n";
}
