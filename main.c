#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Pilha/Pilha.h"

//Constantes Globais
#define Giga 1073741824
#define Mega 1048576
#define Kilo 1024



/* TO DO
implementar leitura para listas
implementar sort salvando em arquivo
implementar leitura indexada do arquivo do sort.
*/

//Programa criar um arquivo bin e manipula informa��es usando as fun��es de escrita e leitura


//Cria��o de uma struct de registro
typedef struct {
	char *nome1, *nome2, *nome3, *equipe;
	int baloes, erros;
}reg;


//FUN��ES declaradas abaixo est�o implementadas depois da main!
int valida(int val);														//confere se n�o passou de 1gb o tamanho solicitado
int escolha_tam(); 															//Menu de tamanhos para escolha
void ler_tudo(FILE *fp,char nome_arq[]); 									//le todo conteudo do arquivo e imprime na tela
int rand_fill(); 															//retorna um int aleatorio
char *randstring(size_t length);											//retorna uma string aleatoria de tamanho espeficado no parametro
double preenche(FILE *fp,int Wanted_size,reg registro,char nome_arq[]); 
int escolhe_menu();
void registra(double registro,FILE *cc, char nome_reg[]);
void lerRegistro(int cont,FILE *fp,char nome_arq[],int opc);
int leQuantReg(FILE *cc,char nome_reg[]);
void paraFila(char *buffer, int t);
void mostra(char *);


int main(int argc, char *argv[]) {

	FILE *fp, *cc; 								//arquivo
	char c;								//char
 	int wanted_size,q,escolha; 
	double reg_total; 						//int
 	reg registro;						//registros
	clock_t start, end;						//variaveis do rel�gio
    char nome_arq[] = "./data.bin";
    char nome_reg[] = "./reg.bin";
    		    
	
								//inicia contagem do tempo
	escolha=escolhe_menu();					//printa menu e retorna o valor da escolha
	
	switch(escolha){
		case 1:
			wanted_size=escolha_tam();			//tamano do arquivo
			start = clock(); 	
			reg_total=preenche(fp,wanted_size,registro,nome_arq);
			registra(reg_total,cc,nome_reg);
			end = clock(); 	
	 		break;
		case 2:	
		   	printf("\n1: Equipe \n2: Erros \n3: Balao \n4: Componente 1 \n5: Componente 2 \n6: Componente 3\nValor digitado:");
			scanf("%i",&escolha);
			int total = leQuantReg(cc,nome_reg);
			lerRegistro(total,fp,nome_arq,escolha);
			break;
		case 3:
			ler_tudo(fp,nome_arq);
			break;
	}
	 //
 	//printf("\nRegistros totais: %1.f",reg_total); 
	
    
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

void mostra(char *p){
	printf("%1.c",*p);
	
}

void ler_tudo(FILE *fp,char nome_arq[]){
   char c;
	fp= fopen(nome_arq, "rb");
  if(fp != NULL)
  {
  	//percorre arquivo at� o final imprimindo na tela
    while((c = fgetc(fp)) != EOF) putchar(c);
    printf("%\n",c);
    fclose(fp);
  }

}

double preenche(FILE *fp,int Wanted_size,reg registro,char nome_arq[]){
	int sz;
	double count;
	//Gera os valores aleat�rios at� encher o arquivo
	count =0;
	if (( fp = fopen(nome_arq,"wb+")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	do{
	/*
		registro.baloes=rand_fill();
		registro.equipe=randstring(20);
		registro.erros=rand_fill();
		registro.nome1=randstring(20);
		registro.nome2=randstring(20);
		registro.nome3=randstring(20);
	*/
	
		registro.equipe="equipe";
	 	registro.erros=4;
		registro.baloes=1;
		registro.nome1="nome1";
		registro.nome2="nome2";
		registro.nome3="nome3";

		//Escreve valores no arquivo
		fwrite(&registro,sizeof(reg),1,fp);
		
		count++;
		
		//printf("\n Inclus�o: %i ,  %i  ,  %s  ,  %s  ,  %s ",registro.baloes,registro.equipe,registro.erros,registro.nome1,registro.nome2,registro.nome3);
		
		fseek(fp, 0L, SEEK_END);  // percorre at� o fim do arquivo 
		sz = ftell(fp);           // informa tamanho e armazena em SZ
		
	}while(sz<Wanted_size);
	
	fclose(fp);
	return count;
}

void lerRegistro(int cont,FILE *fp,char nome_arq[],int opc){
	double valRegistro;
	char * buff;
	int t,size;
	long pos;
	int offset; //variavel aponta para endere�o no arquivo
	reg registroleitura;  //leitura para o registro
	
	fp= fopen(nome_arq, "rb");
	if(fp == NULL){
        perror("fopen\n");
        exit(EXIT_FAILURE);
    }
    	
  	fseek(fp,0,SEEK_SET);
  	
	fread(&registroleitura,sizeof(registroleitura),1,fp);
	
  	switch(opc){
		case 1:
			printf("\n Baloes: %i",registroleitura.baloes);
			break;
		case 2:	
			printf("\n Equipe: %s",registroleitura.equipe);
			break;
		case 3:
			printf("\n Erros: %i",registroleitura.erros);
			break;
		case 4:
			printf("\n Nome1: %s",registroleitura.nome1);
			break;
		case 5:
			printf("\n Nome2: %s",registroleitura.nome2);
			break;
		case 6:
			printf("\n Nome3: %s",registroleitura.nome3);
			break;			
	}	
	close(fp);
	
	
}


//criar arquivo contendo a quantidade de registros inseridos.
void registra(double registro,FILE *cc, char nome_reg[]){
	if (( cc = fopen(nome_reg,"wb+")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	fprintf(cc,"%.0lf",registro);
	fclose(cc);
}
int leQuantReg(FILE *cc,char nome_reg[]){
	int total;
	if (( cc = fopen(nome_reg,"rb+")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	
	//percorre at� o final do arquivo e retorna o tamanho total
  	
	fread(&total,sizeof(int),1,cc);
	
	printf("\nTotal de registros no arquivo: %i",total);
	return total;
}



// funcao para passar informa��es do buffer para listas
void paraPilha(char *buffer, int t){

	int tamanho=t;
	int i;
	char *temp;
	void *buf;
	//!!conferir o tamanho da inicializa��o da lista.!!!
	//inicializa_lista(f,tamanho);
	
	/*
	for(i=0;i<t;i++){
		if(buffer[i]=","){
			i++;	
	}else{
		buf=buffer[i];
		insereNaPos(f, buf, i);
		}
	}	
	*/	
}

//  while( fgets(line, sizeof(line), fp) != NULL)
