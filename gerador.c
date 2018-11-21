#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Arvore.c"

//Constantes Globais
#define Giga 1073741824
#define Mega 1048576
#define Kilo 1024
#define VALL 20
#define nome_arq[] = "./data.bin";
#define nome_reg[] = "./reg.bin";
#define nome_res[] = "./res.bin";


typedef struct {
	char nome1[VALL], nome2[VALL], nome3[VALL], equipe[VALL];
	int baloes, erros;
}reg;

//Cabecalho das funcoes que geram o arquivo
int valida(int val);														//confere se não passou de 1gb o tamanho solicitado
int escolha_tam(); 															//Menu de tamanhos para escolha
void ler_paginacao(FILE *rs,char nome_res[],int paginacao,int registros);	//le conteudo do arquivo de acordo com a paginacao
int rand_fill(); 															//retorna um int aleatorio
char *randstring(size_t length);											//retorna uma string aleatoria de tamanho espeficado no parametro
double preenche(FILE *fp,int Wanted_size,reg registro,char nome_arq[]);     //preenche os arquivo com dados
int escolhe_menu();															//printa menu
void registra(double registro,FILE *cc, char nome_reg[]);					//grava quantidade total de registros no arquivo "./reg.bin"
void lerRegistro(int cont,FILE *fp,char nome_arq[],int opc);				//Le o valor de um campo do registro
double leQuantReg(FILE *cc,char nome_reg[]);								// Recupera quantidade de registros do arquivo reg.bin             

void gerador(int wanted_size){
	double reg_total; 						
	reg registro;
	FILE *cc; 
	
	start = clock(); 
	reg_total=preenche(fp,wanted_size,registro,nome_arq);
	registra(reg_total,cc,nome_reg);
	end = clock();
	
}

double leQuantReg(FILE *cc,char nome_reg[]){
	double total; 
	char *buffer = NULL;
   	int string_size, read_size;
	
	//testa abertura do arquivo
	if (( cc = fopen(nome_reg,"rb")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	
	//busca final do arquivo
	fseek(cc, 0, SEEK_END);
	string_size = ftell(cc);
	rewind(cc);
	
	//aloca buffer
	buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
	
	//efetua leitura
	read_size = fread(buffer, sizeof(char), string_size, cc);
	//marcador de final do buffer
	buffer[string_size] = '\0';
	
	//valida se leitura deu certo
	if (string_size != read_size)
       {
           // Algo deu errado
           // buffer vira NULL
           free(buffer);
           buffer = NULL;
       }
       
	fclose(cc);
	
	
	//converte string para int
	total= atoi(buffer);
	
	//imprime valor
	printf("\nTotal de registros no arquivo: %.0lf",total);
	
	return total;
}

void ler_paginacao(int paginacao){
	 FILE *rs;
	 FILE cc*;
	 
	 leQuantReg(File *cc,char nome_reg)
	 
  	 reg registroleitura [registros];
  	 int string_size,i,t;
  	 //abre o arquivo de resultado
  	if (( rs = fopen(nome_res,"rb")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	
	fseek(rs,0,SEEK_SET);
	
	//valida o tamanho da paginacao passada.
	if(paginacao>registros){
		paginacao=registros;
	}
	t=0;
	while(t<registros){
	
  		//percorre loop da paginacao e exibe na tela
    	for(i=1; i<=paginacao;i++) {	
			fread(&registroleitura[t],sizeof(reg),1,rs);
			printf("\n %i, %s, %i , %s, %s, %s, reg: %i ",registroleitura[t].baloes,registroleitura[t].equipe,registroleitura[t].erros,registroleitura[t].nome1,registroleitura[t].nome2,registroleitura[t].nome3,i);
			t++;
		}	
		//espera imput
		getchar();
		getchar();
	}
	fclose(rs);
  	

}

double preenche(FILE *fp,int Wanted_size,reg registro,char nome_arq[]){
	int sz;
	double count;
	//Gera os valores aleatórios até encher o arquivo
	count =0;
	if (( fp = fopen(nome_arq,"wb")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	do{

		registro.baloes=rand_fill();
		strcpy(registro.equipe,randstring(VALL-1)); 
		registro.erros=rand_fill();
		strcpy(registro.nome1,randstring(VALL-1));
		strcpy(registro.nome2,randstring(VALL-1));
		strcpy(registro.nome3,randstring(VALL-1));


		//Escreve valores no arquivo
		fwrite(&registro,sizeof(reg),1,fp);
		count++;
		
		
		fseek(fp, 0L, SEEK_END);  // percorre até o fim do arquivo 
		sz = ftell(fp);           // informa tamanho e armazena em SZ
		
	}while(sz<Wanted_size);
	
	fclose(fp);
	return count;
}

//criar arquivo contendo a quantidade de registros inseridos.
void registra(double registro,FILE *cc, char nome_reg[]){
	if (( cc = fopen(nome_reg,"wb")) == NULL ){	//abre o arquivo
 		printf ("Erro na abertura do arquivo");
		exit (0);
	}
	fprintf(cc,"%.0lf",registro);
	fclose(cc);
}

