/*****************************************************PRINCIPAL*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "arvore.h"


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
	//os paremtros s�o os dados a serem gravados, o tamanho dos dados,
	// a qtd de unidades a serem gravadas e o ponteiro para o arquivo.
	//a funcao retorna um int. se o retorno for != da qtd de unidades entao � erro na escrita.(VERIFICAR)

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

void leRegistroUsuario(Registro *RegAux) {

	printf("\tNome Completo: ");
	fgets((*RegAux).nomeCompleto, tam, stdin);  //lendo os caracteres digitados pelo usu�rio e colocando na struct. Stdin � a const que representa o keyboard
	printf("\tData Nascimento: ");
	fgets((*RegAux).dataNascimento, tam, stdin);
	printf("\tCPF: ");
	scanf("%d", &(*RegAux).cPF);
	fflush(stdin);
	printf("\tEndere�o: ");
	fgets((*RegAux).endereco, tam, stdin);
	fflush(stdin);
	printf("\tProfiss�o: ");
	fgets((*RegAux).profissao, tam, stdin);
	printf("\tEmail: ");
	fgets((*RegAux).email, tam, stdin);
	printf("\tTelefone Celular: ");
	scanf("%d", &(*RegAux).telCelular);
	printf("\tTelefone Resid�ncial: ");
	scanf("%d", &(*RegAux).telResidencial);
	printf("\tTelefone Comercial: ");
	scanf("%d", &(*RegAux).telComercial);

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

	imprimeRegistro(arquivoPrincipal, Ind1);  //a busca poderia ser feita por qualquer que seja o Ind(Ind1 ou Ind 2) j� que os dois precisam existir

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

	fseek(arquivoPrincipal, Ind->posicao, SEEK_SET); //seek_set � uma constante que indica que a acao deve ser tomada a partir do arquivo
	fwrite(&RegAux, sizeof(Registro), 1, arquivoPrincipal); //leia-se: escreva o conteudo &RegAux, que � o tamanho tal, sendo que � apenas uma unidade deste, no arquivo principal

	fclose(arquivoPrincipal);

}

int main(int argc, char *argv[]) {

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


	Inicializa(&Ap1, &Ap2, &IndAux, &RegAux);    //reserva espa�o para cada vari�vel usando malloc

	carregaArquivoIndice(arquivoIndice, &Ap1, &Ap2, &qntRegistros); //Abertura  de arquivos e leitura at� seu final chamando o metodo insereArvore

	while(1) {
		system("cls");
		printf("AGENDA DE CONTATOS");
		printf("1 - Cadastrar Contato\n");
		printf("2 - Consultar Contato Completo\n");
		printf("3 - Editar Contato\n");
		printf("4 - Excluir Contato\n");
		printf("5 - Imprimir todos os Contatos\n");
		printf("6 - Consultar Contatos pelo nome\n");
		printf("0 - Sair\n");
		fflush(stdin);
		scanf("%c", &opt);
		if(opt=='0') break;
		switch(opt) {
			case '1':
				system("cls");
				printf("AGENDA DE CONTATOS");
				printf("Cadastrar Pessoa\n");
				fflush(stdin);  										// limpa o buffer do teclado no windows
				leRegistroUsuario(&RegAux);							     // m�todo que l� o conte�do digitado pelo user
				strcpy(IndAux.nomeCompleto, RegAux.nomeCompleto);         		    // copia o titulo de RegAux para o titulo de IndAux
				IndAux.telCelular = RegAux.telCelular; 							// copia o codigo de regAux para IndAux

				IndAux.posicao = InsereArquivoPrincipal(arquivoPrincipal, RegAux);    //vai salvar a estrutura principal no arquivo principal
				if(InsereArvore(IndAux, &Ap1, 1) && InsereArvore(IndAux, &Ap2, 2))    //passo a copia do nome e do telefone como param. O ponteiro Ap1 e Ap2 j� estao prontos pois passaram pelo metodo carregaArquivoIndice
					qntRegistros++;
				break;

			case '2':
				system("cls");
				printf("AGENDA DE CONTATOS");
				printf("Consultar Contato: ");
				fflush(stdin);
				fgets(strAux, tam, stdin);       //pega o que � digitado pelo usuario
				x = atoi(strAux);                //converte para inteiro
				if(x!=0) {						 //se for um numero
					IndAux.telCelular = x;
					imprimeRegistro(arquivoPrincipal, PesquisaArvore(IndAux, Ap1, 1)); //a pesquisa esta sendo feita pelo telCelular. O pesquisa arvore retorna um apontador
				} else {
					strcpy(IndAux.nomeCompleto, strAux);
					imprimeRegistro(arquivoPrincipal, PesquisaArvore(IndAux, Ap2, 2));  //a pesquisa sendo feita pelo nome
				}
				printf("\t\t");
				system("pause");
				break;

			case '3':
				system("cls");
				printf("AGENDA DE CONTATOS");
				printf("Contato a ser editado: ");
				fflush(stdin);
				fgets(strAux, tam, stdin);
				x = atoi(strAux);
				if(x!=0) {
					IndAux.telCelular = x;
					IndX = PesquisaArvore(IndAux, Ap1, 1); //verificando se existe na arvore 1
					if(IndX) strcpy(IndAux.nomeCompleto, IndX->nomeCompleto);
					IndY = PesquisaArvore(IndAux, Ap2, 2);   //verificando se existe na arvore 2
					editaRegistro(arquivoPrincipal, IndX, IndY, &Ap1, &Ap2);
				} else {
					strcpy(IndAux.nomeCompleto, strAux);
					IndY = PesquisaArvore(IndAux, Ap2, 2);
					if(IndY) IndAux.telCelular = IndY->telCelular;
					IndX = PesquisaArvore(IndAux, Ap1, 1);
					editaRegistro(arquivoPrincipal, IndX, IndY, &Ap1, &Ap2);
				}
				break;

			case '4':
				system("cls");
				printf("AGENDA DE CONTATOS");
				printf("Contato a ser retirado: ");
				fflush(stdin);
				fgets(strAux, tam, stdin);
				x = atoi(strAux);     //essa conversao e feita para que depois a verificacao possa diferenciar por que metodo sera feita exclusao
				if(x!=0) { 				//se o que o usuario digitou foi numero... se nao foi um texto
					IndAux.telCelular = x;
					IndX = PesquisaArvore(IndAux, Ap1, 1);
					retiraRegistroArquivoPrincipal(arquivoPrincipal, IndX);
					if(IndX) x = Retira(*IndX, &Ap1, 1);  //retirando o contato da arvore 1 reponsavel por telefone
					IndX = PesquisaArvore(IndAux, Ap2, 1);
					if(IndX) x = Retira(*IndX, &Ap2, 2);  //retirando o contato da arvore 2 reponsavel por nome
				} else {
					strcpy(IndAux.nomeCompleto, strAux);
					IndX = PesquisaArvore(IndAux, Ap1, 2);
					retiraRegistroArquivoPrincipal(arquivoPrincipal, IndX);
					if(IndX) x = Retira(*IndX, &Ap1, 1);
					IndX = PesquisaArvore(IndAux, Ap2, 2);
					if(IndX) x = Retira(*IndX, &Ap2, 2);
				}
				if(x==1) {
					printf("Contato excluido com sucesso!\n");
					qntRegistros--;
				} else {
					printf("Erro: Contato nao encontrado.\n");
				}
				system("pause");
				break;

			case '5':
				system("cls");
				printf("AGENDA DE CONTATOS");
				if(!Ap1 || !Ap2) {
					printf("Nenhum Contato cadastrado.\n");
					system("pause");
					break;
				}
				printf("Para Imprimir todos os contatos Ordenados alfebeticamente digite NOME? ");
				fflush(stdin);
				fgets(strAux, tam, stdin);
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
			case '6':
				system("cls");
				printf("AGENDA DE CONTATOS ");
				printf("Digite o nome: ");
				if(!Ap1 || !Ap2) {
					printf("Nenhum Contato cadastrado.\n");
					system("pause");
					break;
				}

				fflush(stdin);

				scanf("%s", &strAux);
				imprimeTodosRegistrosStr(arquivoPrincipal, Ap2, strAux );  //a busca � sempre feita pelo nome ou pedaco dele
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
