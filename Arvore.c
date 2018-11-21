#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define T 2
#define MAX_CHAVES 2*T-1 // qtde max de chaves
#define MAX_FILHOS 2*T // qtde max de filhos
#define MIN_OCUP T-1  // ocupacao min em cada no

typedef struct no_arvoreB arvoreB;

struct no_arvoreB {
	int num_chaves; // qtde chaves do no
	int chaves[ MAX_CHAVES ];
	arvoreB * filhos [ MAX_FILHOS ];
};

void insere_chave( arvoreB *raiz , int info , arvoreB * filhodir ) {
	int k, pos;

// obtem o endereco para insercao da nova chave
	pos = busca_binaria ( raiz , info );
	k = raiz->num_chaves;

// libera espaco para insercao da chave na pagina
	while( k > pos && info < raiz->chaves[ k - 1 ] ) {
		raiz ->chaves[ k ] = raiz->chaves[ k - 1 ];
		raiz ->filhos[ k + 1 ] = raiz->filhos[ k ];
		k--;
	}

// insere a chave
	raiz ->chaves[ pos ] = info;
	raiz ->filhos[ k + 1 ] = filhodir ;
	raiz ->num_chaves++;
}

arvoreB* insere( arvoreB *raiz, int info , bool *h, int *info_retorno ) {
	int i , j , pos, info_mediano;
	arvoreB *temp, *filho_dir ;

	if ( ! raiz ) {
		*h = true; // atingiu no folha
		*info_retorno = info;
		return NULL;
	} else {
		pos = busca_binaria ( raiz , info );
		if ( raiz->num_chaves > pos && raiz->chaves[ pos ] == info ) {
			printf ( "Chave ja contida na arvore " );
			*h = false;
		} else {
			filho_dir = insere( raiz->filhos[ pos ], info , h, info_retorno );
			if ( *h ) {
				if ( raiz->num_chaves < MAX_CHAVES ) { // tem espaco na pagina
					insere_chave ( raiz , *info_retorno , filho_dir );
					*h = false;
				} else { // overflow ! SPLIT-AND-PROMOTE
					temp = ( arvoreB* ) malloc( sizeof ( arvoreB ) );
					temp->num_chaves = 0;
					for ( i = 0; i < MAX_FILHOS; i++ )
						temp->filhos[ i ] = NULL;

					info_mediano = raiz->chaves[ MIN_OCUP ]; // PROMOTE

// insere metade da pagina no temp (SPLIT)
					temp->filhos[ 0 ] = raiz->filhos[ MIN_OCUP + 1 ];
					for ( i = MIN_OCUP + 1; i < MAX_CHAVES; i++ )
						insere_chaves ( temp, raiz->chaves[ i ], raiz->filhos[ i + 1 ] );

// atualiza raiz
					for ( i = MIN_OCUP; i < MAX_CHAVES; i++ ) {
						raiz->chaves[ i ] = 0;
						raiz->filhos[ i + 1 ] = NULL;
					}
					raiz->num_chaves = MIN_OCUP;

// verifica onde inserir a nova chave
					if ( pos <= MIN_OCUP )
						insere_chave ( raiz , *info_retorno , filho_dir );
					else
						insere_chave ( temp, *info_retorno , filho_dir );

					*info_retorno = info_mediano;
					return temp;
				}
			}
		}
	}
}

arvoreB * insere_arvoreB ( arvoreB *raiz , int info ) {
	bool h;
	int info_retorno , i ;
	arvoreB * filho_dir , *nova_raiz ;

	filho_dir = insere( raiz , info , &h, &info_retorno );
	if ( h ) { // aumenta altura da arvore ?
		nova_raiz = ( arvoreB* ) malloc( sizeof ( arvoreB ));
		nova_raiz ->num_chaves = 1;
		nova_raiz->chaves[ 0 ] = info_retorno ;
		nova_raiz->filhos[ 0 ] = raiz;
		nova_raiz->filhos[ 1 ] = filho_dir ;

		for ( i = 2; i <= MAX_CHAVES; i++ )
			nova_raiz->filhos[ i ] = NULL;
		return nova_raiz ;
	} else return raiz ;
}

int busca_binaria( arvoreB *no, int info ) {
	int meio, i = 0, f = no->num_chaves - 1;

	while( i <= f ) {
		meio = ( i + f ) / 2;
		if ( no->chaves[ meio ] == info )
			return meio; // encontrou a posicao da chave procurada
		else if ( no->chaves[ meio ] > info )
			f = meio - 1;
		else
			i = meio + 1;
	}
	return i ; // nao encontrou
}

arvoreB * busca( arvoreB * raiz , int info ) {
	arvoreB * no;
	int pos;

	no = raiz;
	while( no ) {
		pos = busca_binaria( no, info );
		if ( pos < no->num_chaves && no->chaves[ pos ] == info )
			return no;
		else
			no = no->filhos[ pos ];
	}
	return NULL;
}

void em_ordem( arvoreB *raiz ) {
	int i ;

	if ( raiz ) {
		for ( i = 0; i < raiz->num_chaves; i++ ) {
			em_ordem( raiz->filhos[ i ] );
			printf ( "\n%d", raiz->chaves[ i ] );
		}
		nova_raiz( raiz->filhos[ i ] );
	}
}




