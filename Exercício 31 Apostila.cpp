//Exercicio 31
#include <stdio.h>
#include <string.h>
struct cadastro{
	char codigo[20],nome[30],raca[25],niver[10];
};
void pega(cadastro);
void mostra(cadastro);

main(){
	cadastro b1,b2;
	printf("\tBienvenido al menu de cadastro de animales!\n\n");
	printf("==Primeiro animal==\n");
	printf("Digite o codigo do animal: ");		gets(b1.codigo);
	printf("Digite o nome do animal: ");		gets(b1.nome);
	printf("Digite a raca do animal: ");		gets(b1.raca);
	printf("Digite a data de aniversario do animal: ");		gets(b1.niver);
	printf("\n==Segundo animal==\n");
	printf("Digite o codigo do animal: ");		gets(b2.codigo);
	printf("Digite o nome do animal: ");		gets(b2.nome);
	printf("Digite a raca do animal: ");		gets(b2.raca);
	printf("Digite a data de aniversario do animal: ");		gets(b2.niver);
	printf("\n\t====STORING DATA====\n");
	printf("  Dados do primeiro animal:\n");
	mostra(b1);
	printf("\n  Dados do segundo animal:\n");
	mostra(b2);
}
void mostra(cadastro b){
	printf("Codigo de registro: ");		puts(b.codigo);
	printf("Nome: ");	puts(b.nome);
	printf("Raca: ");	puts(b.raca);
	printf("Data de aniversario: ");	puts(b.niver);
}
