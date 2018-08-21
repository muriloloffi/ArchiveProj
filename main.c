#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lista/Lista.h"
#include <time.h>
#include <windows.h>
//Programa criar um arquivo bin e manipula informações usando as funções de escrita e leitura

//Criação de uma struct de registro
typedef struct {
	char *nome1, *nome2, *nome3, *equipe;
	int baloes, erros;
}reg;


//FUNÇÕES declaradas abaixo estão implementadas depois da main!
int valida(int val);
void anyFile_FixedSize(FILE *fp, int wanted_size); //altera o arquivo bin para o tamanho passado.
int escolha_tam(); //Menu de tamanhos para escolha
void ler_tudo(FILE *fp,char nome_arq[]); //le todo conteudo do arquivo e imprime na tela
int rand_fill(); //retorna um int aleatorio
char *randstring(size_t length);//retorna uma string aleatoria de tamanho espeficado no parametro

int main(int argc, char *argv[]) {

	FILE *fp; 								//arquivo
	char c; 								//char
 	int wanted_size; 						//int
 	reg registro, aux;						//registros
	clock_t start, end;						//variaveis do relógio
    char nome_arq[] = "./data.txt";
    
	wanted_size=escolha_tam();				//tamano do arquivo
	start = clock(); 						//inicia contagem do tempo
	
	//Abertura/ criação do arquivo
 	if (( fp = fopen(nome_arq,"w+" )) == NULL ){
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	
	anyFile_FixedSize(fp, wanted_size); 	// aumenta o tamanho do arquivo
	
	
	//Gera os valores aleatórios até encher o arquivo
	do{
	
	registro.baloes=rand_fill();
	registro.equipe=randstring(rand_fill());
	registro.erros=rand_fill();
	registro.nome1=randstring(rand_fill());
	registro.nome2=randstring(rand_fill());
	registro.nome3=randstring(rand_fill());
	
	//Escreve valores no arquivo
	fprintf(fp,"%i,%s,%i,%s,%s,%s$",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);//imprime todos os valores separados por virgulas e com $separando os registros.
	/* Imprime os valores aleatorios escritos no arquivo
	printf("\nInclusao sucesso\n%i\n%s\n%i\n%s\n%s\n%s\n",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);
	*/
	}while((c = fgetc(fp)) != EOF);
	
    fclose(fp);
 	
 	/*  Teste da leitura do arquivo
 	printf("\n\n\nLEITURAASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n\n");
 	ler_tudo(fp,nome_arq);
    */
    
    //Fim ca contagem do tempo e computa tempo total.
	end = clock(); //terminate clock
	printf("tempo utilizado: %.5f",(((double)(end-start)/CLOCKS_PER_SEC)));
    
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

int rand_fill(){
	//gera valor int aleatorio até 99
	int iRand;
	iRand=(rand() % 99);
	return iRand;
}

char *randstring(size_t tam) {
	int n;
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //lista de chars possiveis  
    char *randomString = NULL; //string

    if (tam) { 
        randomString = malloc(sizeof(char) * (tam +1));

        if (randomString) {            
            for ( n = 0;n < tam;n++) {    //for do tamanho         
                int key = rand() % (int)(sizeof(charset) -1); //pega um int do tamanho da lista
                randomString[n] = charset[key];  // a string recebe o char na posicao aleatoria key
            }

            randomString[tam] = '\0'; //final da string
        }
    }

    return randomString;
}

void ler_tudo(FILE *fp,char nome_arq[]){
   char c;
	fp= fopen(nome_arq, "rb");
  if(fp != NULL)
  {
  	//percorre arquivo até o final imprimindo na tela
    while((c = fgetc(fp)) != EOF) putchar(c);
    printf("%[]\n",c);
    fclose(fp);
  }

}

