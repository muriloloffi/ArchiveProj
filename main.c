#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "arvore.h"
#include <time.h>

//Constantes Globais
#define Giga 1073741824
#define Mega 1048576
#define Kilo 1024
#define VALL 20


typedef struct {
	char nome1[VALL], nome2[VALL], nome3[VALL], equipe[VALL];
	int baloes, erros;
} Registro;

void Inicializa(Apontador *Ap1, Apontador *Ap2, Indice *IndAux, Registro *RegAux) {
	*Ap1 = *Ap2 = NULL;
	if(!(IndAux = (Indice*) malloc(sizeof(Indice)))) exit(1);
	if(!(RegAux = (Registro*) malloc(sizeof(Registro)))) exit(1);
}

long InsereArquivoPrincipal(FILE *arquivoPrincipal, Registro RegAux) {

	long posAux;

	//Abre o arquivo para atualizacao (leitura e escrita) por causa do parametro "a+b".
	if(!(arquivoPrincipal = fopen("arquivoPrincipal", "a+b"))) {
		printf("Erro ao abrir arquivo principal.\n");
		system("pause");
		return 1;
	}

	//permite a leitura e escrita randomica, neste caso partindo do final do file de 0 em 0 bytes
	fseek(arquivoPrincipal, 0, SEEK_END);

	//retorna a posicao corrente de leitura ou escrita no arquivo (em bytes), ou seja,
	//ira retornar quantos bytes o arquivo possui
	posAux = ftell(arquivoPrincipal);

	fwrite(&RegAux, sizeof(Registro), 1, arquivoPrincipal);  //o fwrite permite escrever uma estrutura definida pelo programador
	//os paremtros são os dados a serem gravados, o tamanho dos dados,
	// a qtd de unidades a serem gravadas e o ponteiro para o arquivo.
	//a funcao retorna um int. se o retorno for != da qtd de unidades entao é erro na escrita.(VERIFICAR)

	fclose(arquivoPrincipal);

	return(posAux);
}

void carregaArquivoIndice(FILE *arquivoIndice, Apontador *Ap1, Apontador *Ap2, int *qntRegistros) {

	Indice IndAux;

	if(!(arquivoIndice = fopen("arquivoIndiceNome", "rb"))) {  //Deve ser usado para abrir arquivos que nao sao do tipo texto "rb"
		printf("Erro ao abrir arquivo indice.\n");
		system("pause");
		return;
	}

	while(!(feof(arquivoIndice))) {
		fread(&IndAux, sizeof(Indice), 1, arquivoIndice);
		if(feof(arquivoIndice)) break;
		InsereArvore(IndAux, &*Ap1, 1);
		(*qntRegistros)++;
	}

	fclose(arquivoIndice);

	if(!(arquivoIndice = fopen("arquivoIndiceTelefone", "rb"))) {  //Deve ser usado para abrir arquivos que nao sao do tipo texto "rb"
		printf("Erro ao abrir arquivo indice.\n");
		system("pause");
		return;
	}

	while(!(feof(arquivoIndice))) {
		fread(&IndAux, sizeof(Indice), 1, arquivoIndice);
		if(feof(arquivoIndice)) break;
		InsereArvore(IndAux, &*Ap2, 2);
		(*qntRegistros)++;
	}

	fclose(arquivoIndice);
}

void salvaArquivoIndice(FILE *arquivoIndice, Pagina *Ap) {

	int i;

	if(Ap != NULL) {
		for(i=0; i<Ap->n; i++) {
			salvaArquivoIndice(arquivoIndice, Ap->p[i]);
			fwrite(&Ap->r[i], sizeof(Indice), 1, arquivoIndice);
		}
		salvaArquivoIndice(arquivoIndice, Ap->p[i]);
	}

}

Registro pegaRegistroArquivoPrincipal(FILE *arquivoPrincipal, long pos) {

	Registro RegAux;

	if(!(arquivoPrincipal = fopen("arquivoPrincipal", "rb"))) {
		printf("Erro ao abrir arquivo principal.\n");
		system("pause");
		EXIT_FAILURE;
	}

	fseek(arquivoPrincipal, pos, SEEK_SET);

	fread(&RegAux, sizeof(Registro), 1, arquivoPrincipal);

	fclose(arquivoPrincipal);

	return(RegAux);
}

void imprimeRegistro(FILE *arquivoPrincipal, Indice *Ind) {

	Registro RegAux;

	if(Ind==NULL) {
		printf("Erro: Pessoa nao Encontrada.\n");
		return;
	}

	RegAux = pegaRegistroArquivoPrincipal(arquivoPrincipal, Ind->posicao);  //abre o arquivo principal com o indice que veio da busca feita em um das arvores para que seja feita a impressao do conteudo existente

	printf("\tNome Completo: %s", RegAux.nomeCompleto);
	printf("\tData Nascimento: %s", RegAux.dataNascimento);
	printf("\tCPF: %ld\n", RegAux.cPF);
	printf("\tEndereco: %s", RegAux.endereco);
	printf("\tProfissao: %s", RegAux.profissao);
	printf("\tEmail: %s", RegAux.email);
	printf("\tTelefone Residencial: %ld\n", RegAux.telResidencial);
	printf("\tTelefone Celular: %ld\n", RegAux.telCelular);
	printf("\tTelefone Comercial: %ld\n\n", RegAux.telComercial);


}

void imprimeTodosRegistros(FILE *arquivoPrincipal, Apontador Ap) {

	int i;

	if(Ap != NULL) {  //Veriicando se a arvore nao esta vazia
		for(i=0; i<Ap->n; i++) { 			 //dentro da estrutura de um apopntador tem uma var int chamada n
			imprimeTodosRegistros(arquivoPrincipal, Ap->p[i]);
			imprimeRegistro(arquivoPrincipal, &Ap->r[i]);
		}
		imprimeTodosRegistros(arquivoPrincipal, Ap->p[i]);
	}
}

void imprimeTodosRegistrosStr(FILE *arquivoPrincipal, Apontador Ap, const char *str) {

	int i;
	int aux;
	String x;

	if(Ap != NULL) {  //Veriicando se a arvore nao esta vazia
		for(i=0; i<Ap->n; i++) { 			 //dentro da estrutura de um apopntador tem uma var int chamada n
			imprimeTodosRegistros(arquivoPrincipal, Ap->p[i]);
			strcpy(x, Ap->r[i].nomeCompleto);
			aux = strlen(x);
			x[aux-1] = '\0';
			if(StartsWith(x, str)) { // procura por uma substring numa string
				imprimeRegistro(arquivoPrincipal, &Ap->r[i]);

			}
		}
		imprimeTodosRegistros(arquivoPrincipal, Ap->p[i]);
	}
}

void editaRegistro(FILE *arquivoPrincipal, Indice *Ind1, Indice *Ind2, Apontador *Ap1, Apontador *Ap2) {

	Registro RegAux;
	Indice IndAux;

	if(Ind1==NULL || Ind2==NULL) {  //esses indices sao utilizados para saber se o contato existe nas duas arvores diferentes
		printf("Erro: Contato nao encontrado.\n");
		system("pause");
		return;
	}

	imprimeRegistro(arquivoPrincipal, Ind1);  //a busca poderia ser feita por qualquer que seja o Ind(Ind1 ou Ind 2) já que os dois precisam existir

	Retira(*Ind1, &*Ap1, 1);
	Retira(*Ind2, &*Ap2, 2);

	leRegistroUsuario(&RegAux);

	strcpy(IndAux.nomeCompleto, RegAux.nomeCompleto);
	IndAux.telCelular = RegAux.telCelular;

	IndAux.posicao = InsereArquivoPrincipal(arquivoPrincipal, RegAux);

	InsereArvore(IndAux, &*Ap1, 1);
	InsereArvore(IndAux, &*Ap2, 2);

}

void retiraRegistroArquivoPrincipal(FILE *arquivoPrincipal, Indice *Ind) {

	Registro RegAux;

	if(Ind == NULL) {       //se o indice que veio do metodo PesquisaArvore for Null...
		printf("Nao foi possivel retirar o contato da agenda (arquivo principal.)\n");
		system("pause");
		return;
	}

	if(!(arquivoPrincipal = fopen("arquivoPrincipal", "r+b"))) {
		printf("Erro ao abrir arquivo principal.\n");
		system("pause");
		return;
	}

	RegAux.telCelular = -1;

	fseek(arquivoPrincipal, Ind->posicao, SEEK_SET); //seek_set é uma constante que indica que a acao deve ser tomada a partir do arquivo
	fwrite(&RegAux, sizeof(Registro), 1, arquivoPrincipal); //leia-se: escreva o conteudo &RegAux, que é o tamanho tal, sendo que é apenas uma unidade deste, no arquivo principal

	fclose(arquivoPrincipal);

}

int main(int argc, char *argv[]) {

	FILE *fp, *cc , *rs; 								//arquivo
	char c;								//char
 	int paginacao;
	double reg_total; 						//int
 	reg registro;						//registros
//-----------------------------------------------------------
	int x;
	char opt='1';
	String strAux;
	Indice IndAux;
	Registro RegAux;
	Pagina *Ap1, *Ap2;    //criacao de 2 apontadores do tipo pagina para guardar tipos de diferentes de dados
	int qntRegistros=0;
	Indice *IndX, *IndY;
	FILE *arquivoIndice;
	FILE *arquivoPrincipal;


	Inicializa(&Ap1, &Ap2, &IndAux, &RegAux);    //reserva espaço para cada variável usando malloc

	carregaArquivoIndice(arquivoIndice, &Ap1, &Ap2, &qntRegistros); //Abertura  de arquivos e leitura até seu final chamando o metodo insereArvore

	while(1) {
		system("cls");
		printf("1 - Gerar arquivo \n");
		printf("2 - Gerar arvore indexada");
		printf("3 - Imprimir todos os registros por paginação\n");
		printf("0 - Sair\n");
		fflush(stdin);
		scanf("%c", &opt);
		if(opt=='0') break;
		switch(opt) {
			case '1':
				system("cls");
				printf("Gerar arquivo");
				printf("/n Informe o tamanho desejado");
				printf("\nEscolha o tamanho do arquivo:\n 1: 1KB\n 2: 1MB\n 3: 1GB\n 4: Tamanho desejado\nValor digitado:");
				scanf("%i",&escolha);
				fflush(stdin);  										// limpa o buffer do teclado no windows
				gerador(escolha);						     // cria arquivo no tamanho especificado
				break;
			case '2':
				system("cls");
				printf("Indexar para arvore ");
				printf("Digite o campo que deseja indexar ");
				// implementação para arvore
				/*
				IndAux.posicao = InsereArquivoPrincipal(arquivoPrincipal, RegAux);    //vai salvar a estrutura principal no arquivo principal
				if(InsereArvore(IndAux, &Ap1, 1) && InsereArvore(IndAux, &Ap2, 2))    //passo a copia do nome e do telefone como param. O ponteiro Ap1 e Ap2 já estao prontos pois passaram pelo metodo carregaArquivoIndice
					qntRegistros++;
				*/
				break;
			case '3':
				system("cls");
				printf("Imprimir por paginacao");
				printf("\nInforme o tamanho da paginação: ");
				fgets();
				fflush(stdin);
				
				
				
				printf("\n");
				if(strcmpi(strAux, "nome\n")==0) {
					printf("Quantidade total de Contatos: %d\n\n", qntRegistros);
					imprimeTodosRegistros(arquivoPrincipal, Ap2);
				} else if(strcmpi(strAux, "codigo\n")==0) {
					printf("Quantidade total de exemplares: %d\n\n", qntRegistros);
					imprimeTodosRegistros(arquivoPrincipal, Ap1);
				} else {
					printf("Nao eh possivel imprimir por %s", strAux);
					system("pause");
					break;
				}
				system("pause");
				break;
				
				fflush(stdin);

				scanf("%s", &strAux);
				imprimeTodosRegistrosStr(arquivoPrincipal, Ap2, strAux );  //a busca é sempre feita pelo nome ou pedaco dele
				system("pause");
				break;


			default:
				system("cls");
				printf("AGENDA DE CONTATOS");
				printf("Opcao invalida!\n");
				system("pause");
		}
	}
	

	if(!(arquivoIndice = fopen("arquivoIndiceNome", "wb"))) {
		printf("Erro ao abrir arquivo indice.\n");
		system("pause");
		return;
	}

	salvaArquivoIndice(arquivoIndice, Ap1);

	fclose(arquivoIndice);

	if(!(arquivoIndice = fopen("arquivoIndiceTelefone", "wb"))) {
		printf("Erro ao abrir arquivo indice.\n");
		system("pause");
		return;
	}

	salvaArquivoIndice(arquivoIndice, Ap2);

	fclose(arquivoIndice);

	return(0);
}


