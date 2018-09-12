#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <time.h>
#include <conio.h>
#include "Lista/Lista.h"

//Constantes Globais
#define Giga 1073741824
#define Mega 1048576
#define Kilo 1024



/* TO DO

implementar indexação
localizacao de registro.

secundario - implementar um menu melhorado ! , limpar tela , tecla de saida e loop no menu.

*/

//Programa criar um arquivo bin e manipula informações usando as funções de escrita e leitura


//Criação de uma struct de registro
typedef struct {
	char *nome1, *nome2, *nome3, *equipe;
	int baloes, erros;
}reg;


//FUNÇÕES declaradas abaixo estão implementadas depois da main!
int valida(int val);									//confere se não passou de 1gb o tamanho solicitado
int escolha_tam(); 										//Menu de tamanhos para escolha
void ler_tudo(FILE *fp,char nome_arq[]); 				//le todo conteudo do arquivo e imprime na tela
int rand_fill(); 										//retorna um int aleatorio
char *randstring(size_t length);						//retorna uma string aleatoria de tamanho espeficado no parametro
double preenche(FILE *fp,int Wanted_size,reg registro,char nome_arq[]); 
int escolhe_menu();
void registra(double registro,FILE *cc, char nome_reg[]);
void valRegistro(double count,FILE *fp,char nome_arq[]);
							


int main(int argc, char *argv[]) {

	FILE *fp, *cc; 								//arquivo
	char c;								//char
 	int wanted_size,q,escolha; 
	double reg_total; 						//int
 	reg registro;						//registros
	clock_t start, end;						//variaveis do relógio
    char nome_arq[] = "./data.bin";
    char nome_reg[] = "./reg.bin";
    		    
	
								//inicia contagem do tempo
	escolha=escolhe_menu();					//printa menu e retorna o valor da escolha
	
	switch(escolha){
		case 1:
			wanted_size=escolha_tam();			//tamano do arquivo
			start = clock(); 	
			reg_total=preenche(fp,wanted_size,registro,nome_arq);
			end = clock(); 	
	 		break;
		case 2:	
		   	printf("\n1: Equipes \n2: Erros \n3: Balao \n4 Componente 1 \n5 Componente 2 \n6 Componente 3");
			scanf("%i",&escolha);
			//funcao de indexação , incluir relógio
			break;
		case 3:
			ler_tudo(fp,nome_arq);
			break;
		
	}
	
	registra(reg_total,cc,nome_reg); //
 	printf("\nRegistros totais: %1.f",reg_total); 
	
	valRegistro(3,fp,nome_arq);  
    
    //Fim da contagem do tempo e computa tempo total.
	end = clock(); 					//finaliza relogio
	printf("\n\n--------------------------------------------------------------");
	printf("\nTempo utilizado: %.10f\n",(((double)(end-start)/CLOCKS_PER_SEC))); // print do tempo utilizado
    
    
 }

//Menu de selecao do tamanho do arquivo ou valor informado pelo usuario
int escolha_tam(){
	int escolha,val;
	printf("\nEscolha o tamanho do arquivo:\n 1: 1KB\n 2: 1MB\n 3: 1GB\n 4: Tamanho desejado\nValor digitado:");
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

int escolhe_menu(){
	int escolha;
	printf("Escolha a opcao desejada no menu:\n 1: Criar arquivo \n 2: Escolha o campo de indexacao\n 3: Exibir arquivo \nValor digitado:");
	scanf("%i",&escolha);
	return escolha;
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
	//gera valor int aleatorio até 9
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
  	//percorre arquivo até o final imprimindo na tela
    while((c = fgetc(fp)) != EOF) putchar(c);
    printf("%\n",c);
    fclose(fp);
  }

}

double preenche(FILE *fp,int Wanted_size,reg registro,char nome_arq[]){
	int sz;
	double count;
	//Gera os valores aleatórios até encher o arquivo
	count =0;
	if (( fp = fopen(nome_arq,"wb+")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
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
		
		//printf("\n Inclusão: %i ,  %i  ,  %s  ,  %s  ,  %s ",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);
		
		fseek(fp, 0L, SEEK_END);  // percorre até o fim do arquivo 
		sz = ftell(fp);           // informa tamanho e armazena em SZ
		
	}while(sz<Wanted_size);
	
	fclose(fp);
	return count;
}

void valRegistro(double count,FILE *fp,char nome_arq[]){
	double valRegistro;
	//char buff[255];
	char * buff;
	int t,size;
	
	fp= fopen(nome_arq, "rb");
	
	//busca tamanho total do arquivo 
	fseek (fp , 0 , SEEK_END);
  	size = ftell (fp);
  	rewind (fp);
  	
	buff= malloc(sizeof(char)*size);	
	
	valRegistro=((count-1)*88); //tamanho fixo em bits
	printf("\n valor do registro %.0f e: %.0lf",count,valRegistro);
	
	
	t = fread (buff,1,size,fp);
	//fgets(buff)
	printf("\n valor de t:%i",t);
	printf("\n\n Buffer: %s",buff);
	close(fp);
	free(buff);
	
	
}

void registra(double registro,FILE *cc, char nome_reg[]){
	if (( cc = fopen(nome_reg,"wb+")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	fprintf(cc,"%.0lf",registro);
	fclose(cc);
}

