#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int i;
 	char str [30];
}reg;

int main(){
	FILE *fp;
 	int count, size;
 	reg registro, aux;
 	char nome_arq[] = "PRAPRAPRA.bin";
 	registro.i = 100;
 	strcpy ( registro . str ,"valor");

 	if (( fp = fopen( nome_arq, "w+" )) == NULL ){
		printf ("Erro na abertura do arquivo"); 
		exit (0); 
	}

 	size = sizeof((reg)+1);
 	count = 1;
 	if ((fwrite (&registro , size , count, fp)) < count){ 
		 puts ("Erro na operacao de escrita");
		exit (0); 
		}
	rewind(fp);
	fread(&aux, sizeof (reg ),1, fp );
	printf("valores lidos : %i, %s", aux. i ,aux. str );
	fclose(fp);
	printf("\nSUCESO");
	return 0;
}
