#include <stdio.h>
#include <string.h>
#include <locale.h>
struct stFilme{
	char titulo[50];
	char diretor[40];
	char ator_principal[40];
	int ano;
	int oscar;
};

void mostrafilme (stFilme);

main (){
	setlocale(LC_ALL,"Portuguese");
	stFilme meu, seu;
	strcpy(meu.titulo,"2001 A Space Odyssey");
	strcpy(meu.diretor,"Stanley Kubrick");
	strcpy(meu.ator_principal,"Keir Dullea");
	meu.ano = 1968;
	meu.oscar = 4;
	printf("Digite o titulo do filme: ");		gets (seu.titulo);
	printf("Digite o ano de lancamento: ");		scanf("%d", &seu.ano);
	fflush(stdin);
	printf("Digite o nome de seu/sua diretor(a): ");	gets(seu.diretor);		fflush(stdin);
	printf("Digite o nome de seu/sua ator/atriz principal: ");		gets(seu.ator_principal);
	printf("Digite o numero de Oscars ganhados: ");		scanf("%d",&seu.oscar);
	printf("\nMeu filme favorito eh:\n ");
	mostrafilme (meu);
	printf("\n\nE o seu eh:\n ");
	mostrafilme (seu);
}
void mostrafilme (stFilme filme){
	printf("\nNome do filme: ");	puts(filme.titulo);
	if(filme.oscar==0)
		printf("Este filme não ganhou Oscars.\n");
	else
		printf("Ganhador de %d Oscar(s)\n",filme.oscar);
	printf("Dirigido por ");		puts(filme.diretor);
	printf("Cujo ator/atriz principal é ");		puts(filme.ator_principal);
	printf("Ano: %d",filme.ano);
}
