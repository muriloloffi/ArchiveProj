const T = 2,
 MAX_CHAVES = 2 * T - 1, // qtde max de chaves
 MAX_FILHOS = 2 * T, // qtde max de filhos
 MIN_OCUP = T - 1; // ocupacao min em cada no

 typedef struct no arvoreB arvoreB;

 struct no arvoreB {
 	int num_chaves; // qtde chaves do no, 4
 	int chaves[ MAX_CHAVES ];
 	arvoreB * filhos [ MAX_FILHOS ];
 };

void insere_chave ( arvoreB *raiz , int info , arvoreB * filhodir ) {
	int k, pos;

	 // obtem o endereco para insercao da nova chave
	 pos = busca_binaria ( raiz , info );
 	k = raiz->num_chaves;

	 // libera espaco para insercao da chave na pagina
 	while( k > pos && info < raiz->chaves[ k - 1 ] ){
 		raiz ->chaves[ k ] = raiz->chaves[ k - 1 ];
 		raiz ->filhos[ k + 1 ] = raiz->filhos[ k ];
		 k--;
 	}
 	// insere a chave
	raiz ->chaves[ pos ] = info;
 	raiz ->filhos[ k + 1 ] = filhodir ;
 	raiz ->num_chaves++;
 }
 
arvoreB* insere ( arvoreB *raiz, int info , bool *h, int *info_retorno ) {
	 int i , j , pos, info_mediano;
	 arvoreB *temp, *filho_dir ;

 	if ( ! raiz ) {
 		*h = true; // atingiu no folha
 		*info_retorno = info;
 		return NULL;
	}else {
 		pos = busca_binaria ( raiz , info );
 		if ( raiz->num_chaves > pos && raiz->chaves[ pos ] == info ) {
 			printf ( "Chave ja contida na arvore " );
 			*h = false;
 		}else{
 			filho_dir = insere( raiz->filhos[ pos ], info , h, info_retorno );
 			if ( *h ) {
				if ( raiz->num_chaves < MAX_CHAVES ) { // tem espaco na pagina
 					insere chave ( raiz , *info_retorno , filho_dir );
 					*h = false;
			}else{ // overflow ! SPLIT-AND-PROMOTE
				temp = ( arvoreB* ) malloc( sizeof ( arvoreB ) );
				temp->num_chaves = 0;
				for ( i = 0; i < MAX_FILHOS; i++ )
					temp->filhos[ i ] = NULL;
								
				info_mediano = raiz->chaves[ MIN_OCUP ]; // PROMOTE
				// insere metade da pagina no temp (SPLIT)
				temp->filhos[ 0 ] = raiz->filhos[ MIN_OCUP + 1 ];
				for ( i = MIN_OCUP + 1; i < MAX_CHAVES; i++ )
				 	insere chaves ( temp, raiz->chaves[ i ], raiz->filhos[ i + 1 ] );
				
					 // atualiza raiz
				for ( i = MIN_OCUP; i < MAX_CHAVES; i++ ) {
					raiz->chaves[ i ] = 0;
					raiz->filhos[ i + 1 ] = NULL;
 				}
 				raiz->num_chaves = MIN_OCUP;

				// verifica onde inserir a nova chave
				if ( pos <= MIN_OCUP )
					insere chave ( raiz , *info_retorno , filho_dir );
				else
					insere chave ( temp, *info_retorno , filho_dir );
				
				*info_retorno = info_mediano;
				return temp;
 				}
 			}
 		}
 	}
}
 
 arvoreB * insere arvoreB ( arvoreB *raiz , int info ) {
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
 }
 else return raiz ;
}

int busca_binaria ( arvoreB *no, int info ) {
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

void em ordem( arvoreB *raiz ) {
	int i ;

	if ( raiz ) {
 	for ( i = 0; i < raiz->num_chaves; i++ ) {
 		em ordem( raiz->filhos[ i ] );
 		printf ( "\n%d", raiz->chaves[ i ] );
 	}
 	em ordem( raiz->filhos[ i ] );
  	}
}


/*
Data  23/10/2018

Caso o elemento X a ser removido esteja em uma p´agina folha:
1.1 se a p´agina tiver m > n,remover o elemento X da p´agina
1.2 caso contr´ario:
1.2.1 se ambas as p´aginas irm˜as contiverem m = n: concatena¸c˜ao recursiva entre as
p´aginas irm˜as de X ap´os X ser removido (join)
1.2.2 se a p´agina irm˜as `a esquerda de X tiver m > n: o pai de X desce para a
p´agina de X e o antecessor do pai de X ´e promovido para nova_raiz
1.2.3 se a p´agina irm˜as `a direita de X tiver m > n: o pai de X desce para a p´agina
de X e o sucessor do pai de X ´e promovido para nova_raiz
2. Caso o elemento esteja em uma p´agina interna, o elemento deve ser
substitu´ido pelo seu sucessor (ou antecessor) na ´arvore (percurso em
ordem) = processo denominado doa¸c˜ao
No caso de doa¸c˜ao:
2.1 se a p´agina doadora tiver m > n, basta doar um elemento
2.2 se a p´agina doadora tiver m = n:
2.2.1 se alguma das p´aginas irm˜as tiver m > n: redistribui¸c˜ao de elementos entre
p´aginas irm˜as (rota¸c˜ao da sub-´arvore)
2.2.2 caso contr´ario: concatena¸c˜ao recursiva entre p´aginas irm˜as (join)

*/


