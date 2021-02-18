/*
	Trabalho Final - Fundamentos de Processamento de Dados
	Gabriel Gato Piragini Sant'Ana - número 07
	Samuel Sensolo Goldflus - número 32
	Turma 71A
	Ano 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <locale.h>
using namespace std;

//Alterado para 35 linhas e 120 colunas, conforme expansão no 'mode com', para usar gotoxy além de 80x25 
text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 35, 120, 1, 1};

FILE *fp;

void textcolor(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

void cursor (int x){ // mostra ou não o cursor do prompt
	switch (x) {
		case 0: {//ocultar cursor
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {//apresentar cursor
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

void clreol ()
{
   COORD coord;
   DWORD escrito;

   coord.X = vActual.winleft+vActual.curx-1;
   coord.Y = vActual.wintop+vActual.cury-1;
   
   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 
      vActual.screenwidth - vActual.curx + 1, coord, &escrito);
   FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
      vActual.attribute, vActual.screenwidth - vActual.curx + 1, 
      coord, &escrito);
   gotoxy(vActual.curx, vActual.cury);
}

void gotoxy(int x, int y){
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct dados{
	char nome[50];
	char email[40];
	char curso[30];
	struct aniversario{
		int dia,mes,ano;
	}nascimento;
	int codigo;
	char sexo;
	char excluido;
}cadastro;

void cadastrar();	//Opção 1 - Cadastrar alunos
void pesquisar();	//Opção 2 - Pesquisar cadastros
void informacao_do_sistema();	//Opção 3 - Informações do Sistema
void menu();		// Função principal - interconecta todas as outras
void salvar_dados();	// Descarrega os dados do ponteiro no arquivo binário
void abrir_arquivo(const char);		// Abre o arquivo, de um determinado modo (passado por referência)
int checa_chave_primaria();			// Verifica o valor do código (se ele já existe, é negativo, etc.)
void pesquisa_codigo(int);		// Função de pesquisa - realiza a busca de códigos
void pesquisa_nome(int);		// Função de pesquisa - realiza a busca de nomes
void tabela_geral(int);			// Função de pesquisa - exibe todos os dados cadastradas
void mostra_menu();			// Mostra os desenhos do menu
void desenho_lupa();		// Mostra o desenho de uma lupa (na função de pesquisa)
void desenha_lua(int,int);	// Mostra o desenho de um ECLIPSE
void mascara_dados();		// Máscara da entrada de dados
void mostra_cursos();		// Imprime a tabela de cursos disponíveis
void carrega(char, int);	// Animação da tela de carregamento
void imprime_char(char c,int vzs);	// Imprime um caractere *n* vezes

main(){
	setlocale(LC_ALL,"");
	SetConsoleTitle("Trabalho Final - FPD");
	system("mode con:cols=120 lines=35"); //aumenta a tela para 120 colunas e 35 linhas
	menu();
	fclose(fp);
	Sleep(2000);
}

void menu(){
	char tecla;		// Variável - Recebe a tecla digitada pelo usuário
	int lin=14;		// Variável - Define a linha de atuação da seta
	int sair=1;		// Variável - Define a condição de saída
		
	textcolor(15);	 textbackground(LIGHTBLUE); // cor de letra e fundo, respectivamente
	system("cls");
	carrega(183,1);		// O "1" sinaliza que é a exibição do início
	mostra_menu();
	do{
		cursor(0);	//ocultar cursor
		gotoxy(44,14);	printf("Cadastro de alunos");
		gotoxy(44,16);	printf("Pesquisar Cadastros");
		gotoxy(44,18);	printf("Informação sobre o Sistema", 135, 198);
		gotoxy(44,20);	printf("Sair");
		gotoxy(41,lin); 	printf("%c", 62);//62 é o caractere '>'
		tecla=getch();
		gotoxy(41,lin); printf(" ");
		switch(tecla){//movimento das setas
			case 72 : //seta para cima
				lin-=2;
				if(lin<14){
					lin=20;	
				}
				gotoxy(41,lin); printf("%c", 62);
				break;
			case 80 : //seta para baixo
				lin+=2;
				if(lin>20){
					lin=14;
				}
				gotoxy(41,lin); printf("%c", 62);
				break;
		}
		switch(tecla){//Quando teclar enter para escolher opção
			case 13: //teclou enter
				if(lin==14){
					system("cls");
					cadastrar();
					mostra_menu();
				}
				else if(lin==16){
				    system("cls");
					pesquisar();	
					mostra_menu();
				}
				else if(lin==18){
					informacao_do_sistema();
					mostra_menu();
				}
				else if(lin==20){
					carrega(183,2);		// O "2" indica que é o encerramento do programa
					sair=0;
				}
		}
	}while(sair);
	
}

void salvar_dados(){
	char co;
	cursor(0);
	gotoxy(3,25);	printf("- Confirmar dados para gravação? (S ou N):");
	do{
		if(co!='s'&& co!='S'&& co!='n' && co!='N'){
			gotoxy(46,25);	cout<<"  ";
		}
		gotoxy(46,25);	co = getche();
	}while( co!='s'&& co!='S'&& co!='n' && co!='N');
	if( co == 's' || co == 'S' ){
		if(fwrite(&cadastro, sizeof(cadastro), 1, fp) != 1){
			gotoxy(12,27);printf("Erro na escrita do arquivo. Tente novamente!");
		}
		else{
			fflush( fp );//descarrega o buffer no disco
			gotoxy(14,27);	textcolor(GREEN);
			printf("Dados salvos com sucesso!");
		}
	}
	else{
		textcolor(RED);
		gotoxy(14,27);	cout<<"OK. Apagando dados...";
	}
}

void abrir_arquivo(const char modo[]){
	if((fp = fopen("arq_gato_goldflus.bin",modo))==NULL){
		gotoxy(43,9);printf("ERRO! Falha na abertura do arquivo");
		gotoxy(48,11);printf("Encerrando o programa... \n\n\n\n\n");
		Sleep(1600); exit(1);
	}
}

int checa_chave_primaria(){
	int codigo_aux, F;
	do{
		rewind(fp);
		F=0;	
		textcolor(14);
		gotoxy(7,4);	scanf("%d",&codigo_aux);
		if(codigo_aux==0) 
			break;
		
		while(fread(&cadastro,sizeof(cadastro),1,fp)==1){
			if ((cadastro.codigo == codigo_aux && cadastro.excluido=='N') || codigo_aux<0){
				F=1;
			}
		}
		if(F==1){
			gotoxy(18,4);	textcolor(RED);
			cout<<"Código inválido ou indisponível!";	Sleep(2200);
			gotoxy(7,4);	imprime_char(' ',44);
		}
	}while(F==1);
	return codigo_aux;
}

void mascara_dados(){
	textcolor(RED);
	gotoxy(6,2);	cout<<"*Não digitar o cê-cedilha, ou caracteres com acento";
	textcolor(WHITE);
	gotoxy(5,3);	cout<<"- Insira um código numérico para cadastro(0 para encerrar):";
	gotoxy(5,5);	cout<<"- Digite seu nome:     ";
	gotoxy(5,7);	cout<<"- Digite seu gênero[M/F]: ";
	gotoxy(5,8);	cout<<"- Digite o curso desejado: ";
	gotoxy(5,10);	cout<<"- Insira seu e-mail para contato: ";
	gotoxy(5,12);	cout<<"- Informe sua data de nascimento:   /  /";
}

void cadastrar(){
	system("cls");
	abrir_arquivo("ab+");
	char confirma;		// confirma os dados colocados pelo usuário
	int checa;
	do{
		mascara_dados();
		mostra_cursos();
		desenha_lua(79,21);
		textcolor(14);	cursor(1);
		cadastro.codigo=checa_chave_primaria();
		if(cadastro.codigo==0){
			system("cls");	break;
		}
		fflush(stdin);
		do{
			gotoxy(7,6);
			gets(cadastro.nome);
		}while(strlen(cadastro.nome)<1);   // Redigita o nome enquanto o campo estiver vazio
		fflush(stdin);
		//------------------
		do{
			gotoxy(31,7);		cin>>cadastro.sexo;		fflush(stdin);
			if(cadastro.sexo!='M' && cadastro.sexo!='m' && cadastro.sexo!='F' && cadastro.sexo!='f'){
				textcolor(RED);
				gotoxy(31,7);	cout<<"Digite apenas 'M' ou 'F'.";
				Sleep(1650);	textcolor(14);
				gotoxy(31,7);		imprime_char(' ',31);	// Deixa apenas o primeiro caractere do gênero
			}
		}while(cadastro.sexo!='M' && cadastro.sexo!='m' && cadastro.sexo!='F' && cadastro.sexo!='f');
		gotoxy(32,7);		imprime_char(' ',30);	// Deixa apenas o primeiro caractere do gênero
		do{
			gotoxy(7,9);	gets(cadastro.curso);	strlwr(cadastro.curso);
			fflush(stdin);
			if(strstr("python",cadastro.curso)){
				strcpy(cadastro.curso,"Python");	checa=0;
			}
			else if(strstr("java",cadastro.curso)){
				strcpy(cadastro.curso,"Java");	checa=0;
			}
			else if(strstr("php",cadastro.curso)!=0){
				strcpy(cadastro.curso,"PHP");	checa=0;
			}
			else if(strstr("c#c-sharp",cadastro.curso)!=0){
				strcpy(cadastro.curso,"C# (C-sharp)");	checa=0;
			}
			else if(strstr("swift",cadastro.curso)!=0){
				strcpy(cadastro.curso,"Swift");	checa=0;
			}
			else if(strstr("desenvolvimento web",cadastro.curso)){
				strcpy(cadastro.curso,"Desenvolv. WEB");	checa=0;
			}
			else if(strstr("estrutura de dados",cadastro.curso)){
				strcpy(cadastro.curso,"Estrut. de Dados");	checa=0;
			}
			else if(strstr("gestão de ti gestao de ti",cadastro.curso)){
				strcpy(cadastro.curso,"Gestão de TI");	checa=0;
			}
			else if(strstr("engenharia de software",cadastro.curso)){
				strcpy(cadastro.curso,"Eng. de Software");	checa=0;
			}
			else if(strstr("sistemas de informação sistemas de informacao",cadastro.curso)){
				strcpy(cadastro.curso,"Sist. de Inform.");	checa=0;
			}
			else if(strstr("algoritmos",cadastro.curso)){
				strcpy(cadastro.curso,"Algoritmos");
				checa=0;
			}
			else if(strstr("redes de computadores",cadastro.curso)){
				strcpy(cadastro.curso,"Redes de Compts.");
				checa=0;
			}
			else {
				checa=1;
				textcolor(4);
				gotoxy(6,9);	cout<<"Curso inválido! Verifique a escrita.\n";	
				Sleep(1200);	textcolor(14);
				gotoxy(3,9);	imprime_char(' ',40);
			}
		}while(checa);
		do{
			gotoxy(7,11);	cin>>cadastro.email;
			if(strstr(cadastro.email,"@")==0){
				textcolor(RED);
				gotoxy(7,11);	cout<<"Coloque um e-mail válido, por gentileza.";
				Sleep(2000);	textcolor(14);
				gotoxy(7,11);	imprime_char(' ',40);
				fflush(stdin);
			}
		}while(strstr(cadastro.email,"@")==0);
		
		do{
			gotoxy(39,12);	textcolor(14);	cin>>cadastro.nascimento.dia;
			if(cadastro.nascimento.dia<1 || cadastro.nascimento.dia>31){
				textcolor(RED);
				gotoxy(10,13);	cout<<"Data inválida!";
				Sleep(2000);
				gotoxy(39,12);	textcolor(7);	cout<<"  /  /    ";
				gotoxy(10,13);	imprime_char(' ',15);
			}
		}while(cadastro.nascimento.dia<1 || cadastro.nascimento.dia>31);
		
		do{
			textcolor(14);
			gotoxy(42,12);	cin>>cadastro.nascimento.mes;
			if((cadastro.nascimento.mes<1 || cadastro.nascimento.mes>12) || (cadastro.nascimento.mes==2 && cadastro.nascimento.dia>29)){
				textcolor(4);
				gotoxy(10,13);	cout<<"Mês inválido!";
				Sleep(2000);	textcolor(7);
				gotoxy(41,12);	cout<<"/  /    ";
				gotoxy(10,13);	imprime_char(' ',15);
			}
		}while((cadastro.nascimento.mes<1 || cadastro.nascimento.mes>12) || (cadastro.nascimento.mes==2 && cadastro.nascimento.dia>29));
		
		do{
			gotoxy(45,12);	textcolor(14);	cin>>cadastro.nascimento.ano;
			if(2020-cadastro.nascimento.ano<18){
				cout<<"    Você tem menos de 18 anos!\n    Perdão, mas não podemos realizar seu cadastro.";
				Sleep(2000);
				system("cls");	return;
			}
		}while(2020-cadastro.nascimento.ano<18);
		cadastro.excluido='N';
		
		textcolor(1);
		cout<<"\n\n\n\t\t      ";	textbackground(WHITE);
		cout<<"==Saída de dados==";	 textcolor(15);	 textbackground(LIGHTBLUE);
		cout<<"\n      Nome: " << cadastro.nome;
		cout<<"\n      Sexo: " << cadastro.sexo;
		cout<<"\n      Curso: " << cadastro.curso;
		cout<<"\n      E-mail para contato: " << cadastro.email;
		cout<<"\n      Aniversário: " << cadastro.nascimento.dia << "/" << cadastro.nascimento.mes << "/" << cadastro.nascimento.ano;
		cout<<"\n      Código: "<< cadastro.codigo;
		gotoxy(5,14); cout<<"_______________________________________________________";
		for(int i=15;i<=23;i++){		// Imprime as bordas da tabela
			gotoxy(5,i);	cout<<"|";
			gotoxy(59,i);	cout<<"|";
		}
		gotoxy(6,23); cout<<"_____________________________________________________";
		salvar_dados();
		textcolor(14);	gotoxy(14,30);
		cout<<"Pressione qualquer tecla para continuar,";
		gotoxy(19,31);  cout<<"ou ESC para retornar ao menu.";
		confirma=getch();
		system("cls");
		if(confirma==27)
			return;
	}while(true);
	cursor(0);
	textcolor(14);
}

void pesquisar(){
	int voltar=1;
	int lin=12;
	int ln=7;
	char tecla;
	char string_pesquisa[50];

	abrir_arquivo("rb");
	
	do{
		desenho_lupa();
		textbackground(BLUE+BLACK);
		gotoxy(36,5);	imprime_char(' ',47);	//Imprime a moldura do quadro direito
		gotoxy(36,28);	imprime_char(' ',49);
		for(int i=5;i<28;i++){
			gotoxy(36,i);	cout<<"  ";
			gotoxy(83,i);	cout<<"  ";
		}
		textbackground(LIGHTBLUE);
		textcolor(WHITE);
		gotoxy(49,8);	printf("PESQUISA DE CADASTROS");
		gotoxy(47,12);	printf("Pesquisar por nome");
		gotoxy(47,15);	printf("Pesquisar por código");
		gotoxy(47,18);	printf("Tabela Geral");
		gotoxy(47,21);	printf("Voltar ao menu principal");
		gotoxy(44,lin); 	printf("%c", 62);
		tecla=getch();
		gotoxy(44,lin); printf(" ");
		switch(tecla){//movimento das setas
			case 72 : //seta para cima
				lin-=3;
				if(lin<12){
					lin=21;	
				}
				gotoxy(44,lin); printf("%c", 62);
				break;
			case 80 : //seta para baixo
				lin+=3;
				if(lin>21){
					lin=12;
				}
				gotoxy(44,lin); printf("%c", 62);
				break;
		}
		
		switch(tecla){//Quando teclar enter para escolher opção
			case 13: //teclou enter
				if(lin==12){		// Pesquisa por nome
					pesquisa_nome(ln+1);	// Adicionamos uma linha abaixo, para que houvesse espaço para a pesquisa de string
					system("cls");	system("mode con:cols=120 lines=35");
				}
				else if(lin==15){	// Pesquisa por código
					pesquisa_codigo(ln);
					system("cls");	system("mode con:cols=120 lines=35");
				}
				else if(lin==18){	// Tabela geral dos cadastros
					tabela_geral(ln);
					system("cls");	system("mode con:cols=120 lines=35");
				}
				else if(lin==21){	// Voltar ao menu principal
					voltar=0;
				}
		}
	}while(voltar);
	
	system("cls");
}

void pesquisa_codigo(int ln){
	int codigo_auxiliar;	
	int contador;		// Variável auxiliar - lhe é acrescida uma unidade caso algum código seja achado.
	char tecla='R';
	system("cls");	system("mode con:cols=140 lines=35");
	textcolor(BLACK);
		for(int i=7;i<13;i++){	// Imprime as bordas da tabel
			gotoxy(2,i);	cout<<"|";
			gotoxy(139,i);	cout<<"|";
		}
		
		gotoxy(3,10);	imprime_char('-',136);
		
		gotoxy(2,7);	imprime_char('_',138);
		gotoxy(3,12);	imprime_char('_',136);
		
		textbackground(YELLOW+RED);
		gotoxy(21,19);	cout<<"       ";	//Imprime o "E" do quadro central
		gotoxy(21,20);	cout<<"  ";
		gotoxy(21,21);;	cout<<"       ";
		gotoxy(21,22);	cout<<"  ";
		gotoxy(21,23);	cout<<"       ";	//"E"
		gotoxy(29,24);	cout<<"       ";	//Imprime o "C"	do quadro central
		gotoxy(29,25);	cout<<"  ";
		gotoxy(29,26);	cout<<"  ";
		gotoxy(29,27);	cout<<"  ";
		gotoxy(29,28);	cout<<"       ";	//"C"
		
		textbackground(LIGHTGREEN);
		gotoxy(17,17);	imprime_char(' ',23);	//Imprime a moldura do quadro central
		gotoxy(17,30);	imprime_char(' ',23);
		for(int i=18;i<30;i++){
			gotoxy(17,i);	cout<<"  ";
			gotoxy(38,i);	cout<<"  ";
		}
		
		desenha_lua(102,17);
		
	textcolor(LIGHTGRAY);
	gotoxy(4,9);	cout<<"Nome";
	gotoxy(48,9);	cout<<"Código";
	gotoxy(58,9);	cout<<"Curso";
	gotoxy(76,9);	cout<<"E-mail";
	gotoxy(116,9);	cout<<"Data de Nasc.";
	gotoxy(133,9);	cout<<"Sexo";
	gotoxy(10,5);	cout<<"Digite o código a ser pesquisado (0 para encerrar): ";
		
	do{
		contador=0;
		rewind(fp);
		cursor(1);	fflush(stdin);
		gotoxy(62,5); cin>>codigo_auxiliar;
		cursor(0);
		
		while(!feof(fp)){
			if(fread(&cadastro,sizeof(cadastro),1,fp)==1 && cadastro.excluido=='N'){
				if(codigo_auxiliar==0)
					return;
				if(codigo_auxiliar==cadastro.codigo){	//mostrar os dados
					gotoxy(4,11);cout<<cadastro.nome;
			 		gotoxy(49,11);cout<<cadastro.codigo;
			 		gotoxy(58,11);cout<<cadastro.curso;
			 		gotoxy(76,11);cout<<cadastro.email;
					gotoxy(117,11);
			 		if(cadastro.nascimento.dia<10)	// Se o numeral do dia for menor que 10, imprimirá um "0" antes.
			 			cout<<"0";
			 		cout<<cadastro.nascimento.dia<<"/";
					gotoxy(120,11);
					if(cadastro.nascimento.mes<10)	// Se o numeral do mês for menor que 10, imprimirá um "0" antes.
			 			cout<<"0";
					cout<<cadastro.nascimento.mes<<"/"<<cadastro.nascimento.ano;
					gotoxy(134,11);cout<<cadastro.sexo;
			 		contador=1;							
				}				
			}
			
		}
		if(contador==1){	// Se ele encontrou algum código
			gotoxy(55,17);	cout<<"Pressione ESC para sair";	// Depois de digitado o código, é mostrada a mensagem
			gotoxy(56,19);	cout<<"Pressione \"R\" para";
			gotoxy(56,20);	cout<<"redigitar um código";
			do{
				fflush(stdin);	 tecla=getch();
				if(tecla==27)	// Se o "esc" (tecla de escape) for pressionado
					return;
				else if(tecla=='R' || tecla=='r'){	// Tecla que redigita um código
					gotoxy(4,11);	imprime_char(' ',110);
					gotoxy(62,5);	imprime_char(' ',15);
				}
			}while(tecla!=27 && tecla!='R'&& tecla!='r');
			gotoxy(55,17);	imprime_char(' ',25);	// Após o usuário digitar a tecla, a mensagem é apagada
			gotoxy(56,19);	imprime_char(' ',20);
			gotoxy(56,20);	imprime_char(' ',20);
		}
		else{		// Não encontrou nenhuma
				textcolor(RED);
				gotoxy(68,5);	cout<<"Código inexistente!";
				Sleep(1700);
				gotoxy(61,5);	imprime_char(' ',35);
				textcolor(LIGHTGRAY);
		}
	}while(tecla=='R' || tecla=='r');
	system("mode con:cols=120 lines=35");
}

void pesquisa_nome(int ln){
	char tecla='R';
	char string_pesquisa[50], string_auxiliar[50];
	int contador;
	system("mode con:cols=140 lines=35");
	do{
		system("cls");	textcolor(BLACK);
		for(int i=4;i<28;i++){	// Imprime as bordas da tabela
			gotoxy(2,i);	cout<<"|";
			gotoxy(139,i);	cout<<"|";
		}
		for(int co=7;co<26;co+=2){
			gotoxy(3,co);	imprime_char('-',136);
		}
		gotoxy(2,4);	imprime_char('_',138);
		gotoxy(3,27);	imprime_char('_',136);
		textcolor(LIGHTGRAY);
		
		gotoxy(4,6);	cout<<"Nome";
		gotoxy(48,6);	cout<<"Código";
		gotoxy(58,6);	cout<<"Curso";
		gotoxy(77,6);	cout<<"E-mail";
		gotoxy(116,6);	cout<<"Data de Nasc.";
		gotoxy(133,6);	cout<<"Sexo";
		gotoxy(5,3);	cout<<"Digite o nome a ser pesquisado: ";
		
		if(tecla=='R' || tecla=='r'){	// Isso ocorre APENAS se o usuário digitar para recerregar
			rewind(fp);	 contador=0;
			cursor(1);	fflush(stdin);
			gets(string_pesquisa);	strlwr(string_pesquisa);		
			cursor(0);
			ln=8;	contador=0;
		}
	
		if(contador!=0){	// Mostra a string pesquisada (só ocorre quando ela existe)
			gotoxy(37,3);	cout<<string_pesquisa;
		}
	
		while(!feof(fp) && ln<28){
			if(fread(&cadastro,sizeof(cadastro),1,fp)==1 && cadastro.excluido=='N'){
				strcpy(string_auxiliar,cadastro.nome);	 strlwr(string_auxiliar);	
				
				if(ln<28 && strstr(string_auxiliar,string_pesquisa)!=NULL){
					gotoxy(4,ln); cout<<cadastro.nome;
			 		gotoxy(49,ln);cout<<cadastro.codigo;
			 		gotoxy(58,ln);cout<<cadastro.curso;
			 		gotoxy(77,ln);cout<<cadastro.email;
			 		gotoxy(117,ln);
			 		if(cadastro.nascimento.dia<10)	// Se o numeral do dia for menor que 10, imprimirá um "0" antes.
			 			cout<<"0";
			 		cout<<cadastro.nascimento.dia<<"/";
					gotoxy(120,ln);
					if(cadastro.nascimento.mes<10)	// Se o numeral do mês for menor que 10, imprimirá um "0" antes.
			 			cout<<"0";
					cout<<cadastro.nascimento.mes<<"/"<<cadastro.nascimento.ano;
			 		gotoxy(134,ln);cout<<cadastro.sexo;
					contador++;
					ln+=2;	
				}				
			}
		}
		if(contador==0){	  // Apenas se ele não achar a string, imprimirá que não existe.
			textcolor(RED);
			gotoxy(48,10);	cout<<"Nome não encontrado! Verifique a grafia.";
			Sleep(1700);
			gotoxy(39,10);	imprime_char(' ',45);
			gotoxy(38,2);	imprime_char(' ',35);
			textcolor(LIGHTGRAY);
		}
		
		else{
			gotoxy(55,30);	cout<<"Pressione ESC para sair";
			gotoxy(57,32);	cout<<"Pressione \"R\" para";
			gotoxy(57,33);	cout<<"redigitar um nome";
			gotoxy(14,30);	cout<<"<-- Pressione \"K\" para";
			gotoxy(15,31);	cout<<"retornar à página inicial";
			gotoxy(94,30);	cout<<"Pressione \"L\" para avançar -->";
			gotoxy(97,31);	cout<<"para a próxima página";
			do{
				fflush(stdin);	 tecla=getch();
				if(tecla==27)	// Se o "esc" (tecla de escape) for pressionado
					return;
				if(tecla=='L' || tecla=='l'){
					ln=8;
					if(feof(fp))
						rewind(fp);
				}
				else if(tecla=='K' || tecla=='k'){
					rewind(fp);
					ln=8;							
				}	
			}while(tecla!='R'&& tecla!='r' && tecla!='L' && tecla!='l' && tecla!='K' && tecla!='k' && tecla!=27);
		}
		
	}while(tecla!=27);
	system("mode con:cols=120 lines=35");
}

void tabela_geral(int ln){
	char tecla;
	rewind(fp);
	system("mode con:cols=140 lines=35");
	do{
		system("cls");
		
		textcolor(BLACK);
		for(int i=3;i<27;i++){	// Imprime as bordas da tabela
			gotoxy(2,i);	cout<<"|";
			gotoxy(139,i);	cout<<"|";
		}
		for(int co=6;co<26;co+=2){
			gotoxy(3,co);	imprime_char('-',136);
		}
		gotoxy(2,3);	imprime_char('_',138);
		gotoxy(3,26);	imprime_char('_',136);
		textcolor(LIGHTGRAY);
		
		gotoxy(4,5);	cout<<"Nome";
		gotoxy(48,5);	cout<<"Código";
		gotoxy(58,5);	cout<<"Curso";
		gotoxy(77,5);	cout<<"E-mail";
		gotoxy(116,5);	cout<<"Data de Nasc.";
		gotoxy(133,5);	cout<<"Sexo";
			
		while(!feof(fp) && ln<26){
			if(fread(&cadastro,sizeof(cadastro),1,fp)==1 && cadastro.excluido=='N'){
				// Verifique se a quantidade de linhas definidas para a janela de exibição foi preenchida (if)
				gotoxy(4,ln); cout<<cadastro.nome;
		 		gotoxy(49,ln);cout<<cadastro.codigo;
		 		gotoxy(58,ln);cout<<cadastro.curso;
		 		gotoxy(77,ln);cout<<cadastro.email;
		 		gotoxy(117,ln);
			 	if(cadastro.nascimento.dia<10)	// Se o numeral do dia for menor que 10, imprimirá um "0" antes.
			 		cout<<"0";
			 	cout<<cadastro.nascimento.dia<<"/";
				gotoxy(120,ln);
				if(cadastro.nascimento.mes<10)	// Se o numeral do mês for menor que 10, imprimirá um "0" antes.
			 		cout<<"0";
				cout<<cadastro.nascimento.mes<<"/"<<cadastro.nascimento.ano;
				gotoxy(134,ln);cout<<cadastro.sexo;
				ln+=2;
			}
		}
		gotoxy(56,30);	cout<<"Pressione ESC para sair";
		gotoxy(16,30);	cout<<"<-- Pressione \"K\" para";
		gotoxy(17,31);	cout<<"retornar à página inicial";
		gotoxy(96,30);	cout<<"Pressione \"L\" para avançar -->";
		gotoxy(99,31);	cout<<"para a próxima página";
		do{
			tecla=getch();
			if(tecla=='L' || tecla=='l'){
				ln=7;
				if(feof(fp))
					rewind(fp);
			}
			else if(tecla=='K' || tecla=='k'){
				ln=7;
				rewind(fp);
			}	
		}while(tecla!='L' && tecla!='l' && tecla!='K' && tecla!='k' && tecla!=27);
		
	}while(tecla!=27);
	system("mode con:cols=120 lines=35");
}

void informacao_do_sistema(){
	system("cls");
	textbackground(WHITE);	textcolor(1);
	gotoxy(50,7);	cout<<"== Empresas Eclipse ==";
	
	textbackground(LIGHTBLUE);	textcolor(YELLOW);
	gotoxy(31,9);	cout<<"Integrantes:";
	gotoxy(31,13);	cout<<"Turma:";
	gotoxy(31,15);	cout<<"Versão atual do Software:";
	gotoxy(31,17);	cout<<"Descrição:";
	
	textcolor(WHITE);
	gotoxy(34,10);	cout<<"Gabriel Gato Piragini Sant'Ana - n 07";
	gotoxy(34,11);	cout<<"Samuel Sensolo Goldflus - n 32";
	gotoxy(38,13);	cout<<"71A";
	gotoxy(57,15);	cout<<"2.1";
	gotoxy(33,18);	cout<<"Neste programa, desenvolvemos um software de uma empresa";
	gotoxy(33,19);	cout<<"fictícia que busca fielmente representar um sistema de";
	gotoxy(33,20);	cout<<"cadastro para alunos em uma escola da área de TI, coletando";
	gotoxy(33,21);	cout<<"dados como nome, e-mail, data de nascimento e gênero.";
	gotoxy(33,22);  cout<<"Gostaríamos de agradecer à professora Ariane Scarelli por";
	gotoxy(33,23);	cout<<"seu fundamental papel como nossa mentora, além de sua";
	gotoxy(33,24);	cout<<"imensa disponibilidade, sempre prestando auxílio e atenção";
	gotoxy(33,25);	cout<<"quando necessário, nos ajudando a traçar este caminho.";
	
	textbackground(BLUE+BLACK);
	gotoxy(25,4);	imprime_char(' ',70);	//Imprime a moldura do quadro direito
	gotoxy(25,32);	imprime_char(' ',72);
	for(int i=4;i<32;i++){
		gotoxy(25,i);	cout<<"  ";
		gotoxy(95,i);	cout<<"  ";
	}
	textbackground(LIGHTBLUE);
	gotoxy(36,28); cout<<"Pressione qualquer tecla para retornar ao menu.";
	getch();
	system("cls");
}

//Funções Adicionais

void imprime_char(char c,int vzs){
	for(int i=0;i<vzs;i++)
		cout<<c;
}

void carrega(char letra,int vez){ //função que simula uma tela de carregamento
	int x,y;	//coordenadas
	int tempo;	//define o tempo no qual o simbolo aparece ou some
	char slv=letra;	//mantém o caractere, para que o espaço possa ser imprimido
	system("cls");	cursor(0);
	if(vez==1){		//	"1" é para o início do programa
		gotoxy(47,5);	cout<<"Eclipse Instituições";
		gotoxy(42,6);	cout<<"Os melhores cursos da área de TI!";
	}
	else if(vez==2){		// "2" é para o encerramento do programa.
		gotoxy(37,6);	cout<<"Obrigado por ter utilizado nossos sistemas!";
		gotoxy(50,9);	cout<<"Encerrando . . .";
	}
	if(vez!=2){		
		gotoxy(50,9);	cout<<"Carregando . . .";
	}
	for(int i=0;i<12;i++){
		if(i%2==0){
			letra=slv;	tempo=13;
		}
		else{
			letra=' ';	tempo=18;
		}
		x=52;	y=13;
		gotoxy(x,y);	cout<<letra;
		x+=2;	y--;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		Sleep(tempo);	x+=2;
		gotoxy(x,y);	cout<<letra;
		Sleep(tempo);	x+=2;
		gotoxy(x,y);	cout<<letra;
		y++;	x+=2;	Sleep(tempo);
		gotoxy(x,y); 	cout<<letra;
		x++;	y++;	Sleep(tempo);
		gotoxy(x,y); 	cout<<letra;
		y++;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		x--;	y++;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		x-=2;	y++;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		x-=2;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		x-=2;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		x-=2;	y--;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		x--;	y--;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
		y--;	Sleep(tempo);
		gotoxy(x,y);	cout<<letra;
	}
	system("cls");
}

void mostra_menu(){
	textbackground(14);
	gotoxy(27,5);	cout<<"       ";	//Imprime o "E"
	gotoxy(27,6);	cout<<"  ";
	gotoxy(27,7);	cout<<"       ";
	gotoxy(27,8);	cout<<"  ";
	gotoxy(27,9);	cout<<"       ";	//"E"
	gotoxy(36,5);	cout<<"       ";	//Imprime o "C"
	gotoxy(36,6);	cout<<"  ";
	gotoxy(36,7);	cout<<"  ";
	gotoxy(36,8);	cout<<"  ";
	gotoxy(36,9);	cout<<"       ";	//"C"
	for(int i=5;i<10;i++){		//Imprime o "L"
		gotoxy(45,i);
		cout<<"  ";
		if(i==9)
			cout<<"     ";
	}//"L"
	for(int i=5;i<10;i++){		//Imprime o "I"
		gotoxy(54,i);
		cout<<"  ";
	}//"I" 
	for(int i=5;i<10;i++){		//Imprime o "P"
		gotoxy(58,i);
		cout<<"  ";
		if(i==5 || i==7)
			cout<<"     ";
	}
	gotoxy(63,6);	cout<<"  "; //"P"
	for(int i=5;i<10;i++){		//Imprime o "S"
		gotoxy(67,i);
		cout<<"  ";
		if(i==5 || i==7 || i==9)
			cout<<"     ";
	}
	gotoxy(72,8);	cout<<"  ";
	textbackground(LIGHTBLUE);
	gotoxy(67,8);	cout<<"  ";
		//"S"
	textbackground(14);
	gotoxy(76,5);	cout<<"       ";	//Imprime o "E"
	gotoxy(76,6);	cout<<"  ";
	gotoxy(76,7);	cout<<"       ";
	gotoxy(76,8);	cout<<"  ";
	gotoxy(76,9);	cout<<"       ";	//"E"
	
	textbackground(LIGHTBLUE);
	gotoxy(31,11);	cout<<"Instituições - os melhores cursos de TI do Brasil";
	
	//Imprime o Lapis:
	textcolor(0);
	gotoxy(14,10);	cout<<"/";
	textbackground(0);
	cout<<" ";	textbackground(LIGHTBLUE);
	cout<<"\\";
	gotoxy(13,11);	cout<<"/";
	textbackground(14);
	cout<<"___";	textbackground(LIGHTBLUE);
	cout<<"\\";
	gotoxy(12,12);	cout<<"/";
	textbackground(14);
	cout<<"     ";	textbackground(LIGHTBLUE);
	cout<<"\\";
	gotoxy(11,13);	cout<<"/";
	textbackground(14);
	cout<<"_______";	textbackground(LIGHTBLUE);
	cout<<"\\";
	textbackground(LIGHTBLUE);
	for(int k=14;k<36;k++){		
		gotoxy(10,k);	
		cout<<"|";
		textbackground(6);
		imprime_char(' ',9);
		textbackground(LIGHTBLUE);
		cout<<"|";		
	}//Imprime o Lapis
	textbackground(BLACK);
	for(int colu=14;colu<36;colu++){	// Imprime as listras do lápis
		for(int k=12;k<19;k+=2){
			gotoxy(k,colu);	cout<<" ";
		}
	}	// Imprime as listras do lápis
	textbackground(1);	// Imprime a borda
	for(int i=0;i<36;i++){
		gotoxy(0,i);	cout<<"  ";
		gotoxy(119,i);	cout<<"  ";
	}
	for(int j=0;j<121;j++ ){
		gotoxy(j,1);	cout<<" ";
	}	// Imprime a borda
	
	textbackground(6);
	gotoxy(19,34);	cout<<" ";
	
	textbackground(LIGHTBLUE);
	gotoxy(20,34);	cout<<"|    ";
	textcolor(15);
	
	textbackground(YELLOW+RED);
	gotoxy(90,13);	cout<<"       ";	//Imprime o "E" do quadro direito
	gotoxy(90,14);	cout<<"  ";
	gotoxy(90,15);;	cout<<"       ";
	gotoxy(90,16);	cout<<"  ";
	gotoxy(90,17);	cout<<"       ";	//"E"
	gotoxy(98,18);	cout<<"       ";	//Imprime o "C"	do quadro direito
	gotoxy(98,19);	cout<<"  ";
	gotoxy(98,20);	cout<<"  ";
	gotoxy(98,21);	cout<<"  ";
	gotoxy(98,22);	cout<<"       ";	//"C"
	
	textbackground(LIGHTGREEN);
	gotoxy(86,11);	imprime_char(' ',23);	//Imprime a moldura do quadro direito
	gotoxy(86,24);	imprime_char(' ',23);
	for(int i=12;i<24;i++){
		gotoxy(86,i);	cout<<"  ";
		gotoxy(107,i);	cout<<"  ";
	}
	textbackground(LIGHTBLUE);
}

void desenho_lupa(){
	textbackground(BLACK);
	gotoxy(96,4);	imprime_char(' ',15);	// Imprime a circunferencia da lente
	for(int i=5;i<13;i++){ 
		if(i==5 || i==12){
			gotoxy(94,i);	cout<<"  ";
			gotoxy(111,i);	cout<<"  ";	
		}
		else{
			gotoxy(92,i);	cout<<"  ";
			gotoxy(113,i);	cout<<"  ";
		}
		
	}
	gotoxy(96,13);	imprime_char(' ',15);	// Imprime a circunferencia da lente
	
	textbackground(15);		 				// Imprime a lente
	gotoxy(96,5);	imprime_char(' ',15);
	for(int i=6;i<12;i++){ 	
		gotoxy(94,i);	imprime_char(' ',19);
	}	
	gotoxy(96,12);	imprime_char(' ',15);	// Imprime a lente
	
	textbackground(7);		// Imprime o reflexo da lente
	for(int i=6;i<12;i++){
		gotoxy(95,i);	cout<<"   ";
	}
	gotoxy(97,12);	cout<<"   ";
							// Imprime o reflexo da lente
	
	textbackground(BLACK);	 // Imprime o cabo
	for(int i=13;i<24;i++){ 
		gotoxy(101,i);	imprime_char(' ',5);
	}
	//gotoxy(96,13);	imprime_char(' ',15);	// Imprime o cabo
	
	textbackground(YELLOW+RED);
	gotoxy(11,11);	cout<<"       ";	//Imprime o "E" do quadro esquerdo
	gotoxy(11,12);	cout<<"  ";
	gotoxy(11,13);;	cout<<"       ";
	gotoxy(11,14);	cout<<"  ";
	gotoxy(11,15);	cout<<"       ";	//"E"
	gotoxy(19,16);	cout<<"       ";	//Imprime o "C"	do quadro esquerdo
	gotoxy(19,17);	cout<<"  ";
	gotoxy(19,18);	cout<<"  ";
	gotoxy(19,19);	cout<<"  ";
	gotoxy(19,20);	cout<<"       ";	//"C"
	
	textbackground(LIGHTGREEN);
	gotoxy(7,9);	imprime_char(' ',23);	//Imprime a moldura do quadro esquerdo
	gotoxy(7,22);	imprime_char(' ',23);
	for(int i=10;i<23;i++){
		gotoxy(7,i);	cout<<"  ";
		gotoxy(28,i);	cout<<"  ";
	}
	
	textbackground(LIGHTBLUE);
}

void desenha_lua(int x,int y){		// passando 94 e 9 de parâmetro
	textbackground(BLACK);	cursor(0);
	int i,j;
	gotoxy(x,y);	imprime_char(' ',17);	// Imprime a circunferencia do eclipse
	for(i=y+1;i<(y+13);i++){ 
		if(i==(y+1) || i==(y+12)){
			gotoxy(x-2,i);	imprime_char(' ',21);
		}
		else if(i==(y+2) || i==(y+11)){
			gotoxy(x-4,i);	imprime_char(' ',25);
		}
		else{
			gotoxy(x-6,i);	imprime_char(' ',29);
		}
	}
	gotoxy(x,y+13);	imprime_char(' ',17);	// Imprime a circunferencia do eclipse
	
	textbackground(YELLOW);					// Imprime a lua
	for(i=(y+4);i<=(y+9);i++){
		gotoxy(x-6,i);
		if(i==(y+4) || i==(y+9))
			cout<<"          ";
		else
			cout<<"        ";
	}
	
	j=(x-7);
	for(i=(y+3);i>(y-1);i--){
		gotoxy(j+2,i);   imprime_char(' ',10);
		j+=2;
	}
	
	j=(x-7);
	for(i=(y+10);i<(y+14);i++){
		gotoxy(j+2,i);   imprime_char(' ',10);
		j+=2;
	}		// Imprime a lua
	textbackground(LIGHTBLUE);
}

void mostra_cursos(){
	textcolor(WHITE);
	gotoxy(62,4);
	imprime_char('_',48);	//topo da tabela
	gotoxy(62,5);
	for(int j=5;j<22;j++){
		cout<<"|"; 	// Lado esquerdo da tabela
		if(j==21)		//Final da tabela
			imprime_char('-',46);
		else
			imprime_char(' ',46);	// Imprime os espaços em "branco"
		cout<<"|";	// Lado direito da tabela
		gotoxy(62,j);
	}
	for(int k=8;k<20;k++){
		gotoxy(85,k);
		cout<<"|";
	}
	gotoxy(63,7);  imprime_char('-',46);
	gotoxy(77,6);	cout<<"Cursos Disponíveis";
	gotoxy(71,8);	cout<<"Python";
	gotoxy(95,8);	cout<<"Java";
	gotoxy(65,10);	cout<<"Desenvolvimento WEB";
	gotoxy(92,10);	cout<<"C#(C-sharp)";
	gotoxy(72,12);	cout<<"PHP";
	gotoxy(95,12);	cout<<"Swift";
	gotoxy(65,14);	cout<<"Estrutura de Dados";
	gotoxy(87,14);	cout<<"Engenharia de Software";
	gotoxy(87,16);	cout<<"Sistemas de Informação";
	gotoxy(68,16);	cout<<"Gestão de TI";
	gotoxy(69,18);	cout<<"Algoritmos";
	gotoxy(87,18);	cout<<"Redes de Computadores";
	gotoxy(1,1);
}
