#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lista/Lista.h"
//Programa criar um arquivo bin e manipula informações usando as funções de escrita e leitura

typedef struct {
	char *nome1, *nome2, *nome3, *equipe;
	int baloes, erros;
}reg;


//FUNÇÕES declaradas abaixo estão implementadas depois da main!
int valida(int val);
void anyFile_FixedSize(FILE *fp, int wanted_size);
int escolha_tam();
void ler_tudo(FILE *fp,char nome_arq[]);

int main(int argc, char *argv[]) {

	FILE *fp;  								//arquivo
 	int wanted_size; //int count, size; 	//int
 	reg registro, aux;						//registros
	clock_t t, end;						//variaveis do relógio
    double *cpu_time_used = NULL;			//tempo de processamento
    char nome_arq[] = "./data.txt";
    
	wanted_size=escolha_tam();				//tamano do arquivo


 	if (( fp = fopen(nome_arq,"w+" )) == NULL ){
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	
	anyFile_FixedSize(fp, wanted_size);
	
	//atribuicoes , deve alterar para valores aleatorios
	registro.baloes=1;
	registro.equipe="c";
	registro.erros=0;
	registro.nome1="Guilherme";
	registro.nome2="Murilo";
	registro.nome3="Joao";
	
	fprintf(fp,"%i,%s,%i,%s,%s,%s",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);//imprime todos os valores separados por virgulas e com $separando os registros.
	printf("Inclusao sucesso;");
	
    fclose(fp);
 
//Reimplementando relógio    
//    t = clock() -t; //terminate clock
//    *cpu_time_used = ((double)t)/ CLOCKS_PER_SEC;
//    printf("tempo utilizado: %.2f", *cpu_time_used);
    
 }

//Menu de selecao do tamanho do arquivo ou valor informado pelo usuario
int escolha_tam(){
	int escolha,val;
	printf("Escolha o tamanho do arquivo:\n 1: 1KB\n 2: 1MB\n 3: 1GB\n 4: Custom Bytes\n\nValor digitado:");
	scanf("%i",&escolha);
	switch(escolha){
	 	case 1:
	 		val = 1024; //1KB
	 		break;
		case 2:
			val = 1048576; //1 MB
			break;
		case 3:
			val= 1073741824; //1GB
			break;
		case 4:
			printf("Informe valor em bytes:");
			scanf("%i",&escolha);
			if(valida(escolha)==0){
				val=escolha;
			}else{
				printf("\nCriado no tamanho padrao de 1 KB!");
				val=1024;
			}
			break;
		default:
			val= 1;
			break; 	
	 }
	return val;
}

//funcao que verifica se o tamanho maximo nao ultrapassou o limite de 1 GB
int valida(int val){
	if(val>1073741824){
		printf("\nArquivo ultrapassa o tamanho maximo de 1 GB!\n");
		return 1;
	}
	return 0;
}

void anyFile_FixedSize(FILE *fp, int wanted_size){
	//definicao do tamanho do arquivo atravez do fseek
  	fseek(fp, wanted_size - 1, SEEK_SET);
    // Write at least one byte to extend the file (if necessary).
    fwrite("", 1, sizeof(char), fp);
    rewind(fp); // retorna ao começo do arquivo
}

void rand_fill(){
	//reg.baloes=rand(int);
	//reg.equipe=rand();
}

void ler_tudo(FILE *fp,char nome_arq[]){
   char c;
	fp= fopen(nome_arq, "r");
  if(fp != NULL)
  {
    while((c = fgetc(fp)) != EOF) putchar(c);
    printf("%[]\n",c);
    fclose(fp);
  }

}
