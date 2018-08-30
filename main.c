#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lista/Lista.h"
#include <time.h>
#define Giga 1073741824
#define Mega 1048576
#define Kilo 1024
//Programa criar um arquivo bin e manipula informa��es usando as fun��es de escrita e leitura

//Cria��o de uma struct de registro
typedef struct {
	char *nome1, *nome2, *nome3, *equipe;
	int baloes, erros;
}reg;


//FUN��ES declaradas abaixo est�o implementadas depois da main!
int valida(int val);									//confere se n�o passou de 1gb o tamanho solicitado
int escolha_tam(); 										//Menu de tamanhos para escolha
void ler_tudo(FILE *fp,char nome_arq[]); 				//le todo conteudo do arquivo e imprime na tela
int rand_fill(); 										//retorna um int aleatorio
char *randstring(size_t length);						//retorna uma string aleatoria de tamanho espeficado no parametro



int main(int argc, char *argv[]) {

	FILE *fp; 								//arquivo
 	int wanted_size,q,sz;
	double count; 						//int
 	reg registro;						//registros
	clock_t start, end;						//variaveis do rel�gio
    char nome_arq[] = "./data.bin";
    		    
	wanted_size=escolha_tam();				//tamano do arquivo
	start = clock(); 						//inicia contagem do tempo
	
	//Abertura/ cria��o do arquivo
 	if (( fp = fopen(nome_arq,"wb+" )) == NULL ){
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	
	
	//Gera os valores aleat�rios at� encher o arquivo
	count =0;
	do{
	
		registro.baloes=rand_fill();
		registro.equipe=randstring(20);
		registro.erros=rand_fill();
		registro.nome1=randstring(20);
		registro.nome2=randstring(20);
		registro.nome3=randstring(20);
	

		//Escreve valores no arquivo
		fprintf(fp,"%i,%s,%i,%s,%s,%s\n",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);//imprime todos os valores separados por virgulas e com $separando os registros.
		
		count++;
		
		//printf("\n Inclus�o: %i ,  %i  ,  %s  ,  %s  ,  %s ",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);
		
		fseek(fp, 0L, SEEK_END);  // percorre at� o fim do arquivo 
		sz = ftell(fp);           // informa tamanho e armazena em SZ
		
	}while(sz<wanted_size);
	
    fclose(fp);
 	
 	printf("\nRegistros totais: %1.f",count);
    
    //Fim da contagem do tempo e computa tempo total.
	end = clock(); 					//finaliza relogio
	printf("\n\n--------------------------------------------------------------");
	printf("\nTempo utilizado: %.10f\n",(((double)(end-start)/CLOCKS_PER_SEC))); // print do tempo utilizado
    
    printf("\nDeseja ler o arquivo? tecle 1\n    ");
    scanf("%i",&q);
    if(q==1){
    	ler_tudo(fp,nome_arq); // funcao para ler todo arquivo e imprimir na tela
	}
    
 }

//Menu de selecao do tamanho do arquivo ou valor informado pelo usuario
int escolha_tam(){
	int escolha,val;
	printf("Escolha o tamanho do arquivo:\n 1: 1KB\n 2: 1MB\n 3: 1GB\n 4: Tamanho desejado\n\nValor digitado:");
	scanf("%i",&escolha);
	switch(escolha){
	 	case 1:
	 		val = Kilo; //1KB
	 		break;
		case 2:
			val = Mega; //1 MB
			break;
		case 3:
			val= Giga; //1GB
			break;
		case 4:
			printf("Informe o tamanho do arquivo em bytes:");
			scanf("%i",&escolha);
			if(valida(escolha)==0){
				val=escolha;
			}else{
				printf("\nCriado com 1 registro!");
				val=1;
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
	if(val>Giga){
		printf("\nArquivo ultrapassa o tamanho maximo de registros +1GB!\n");
		return 1;
	}
	return 0;
}

int rand_fill(){
	//gera valor int aleatorio at� 9
	int iRand;
	iRand=(rand() % 9);
	return iRand;
}

char *randstring(size_t tam) {
	int n;
    static char charset[] = "abcdefghijklmnopqrstuvwxyz"; 	//lista de chars possiveis  
    char *randomString = NULL; //string

    randomString = malloc(sizeof(char) * (tam +1));         //aloca tamanho da string  
    for ( n = 0;n < tam;n++) {    							//for do tamanho         
    	int key = rand() % (int)(sizeof(charset) -1); 		//pega um int do tamanho da lista
		randomString[n] = charset[key];  					// a string recebe o char na posicao aleatoria sorteada acima
    }

    randomString[tam] = '\0'; 								//final da string
    return randomString; 									// retorna valor 
}

void ler_tudo(FILE *fp,char nome_arq[]){
   char c;
	fp= fopen(nome_arq, "rb");
  if(fp != NULL)
  {
  	//percorre arquivo at� o final imprimindo na tela
    while((c = fgetc(fp)) != EOF) putchar(c);
    fclose(fp);
  }

}

