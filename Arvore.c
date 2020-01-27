const T = 2,
      MAX CHAVES = 2 * T - 1, // qtde max de chaves
          MAX FILHOS = 2 * T, // qtde max de filhos
              MIN OCUP = T - 1; // ocupacao min em cada no

typedef struct no arvoreB arvoreB;

struct no arvoreB {
	int num chaves; // qtde chaves do no
	int chaves[ MAX CHAVES ];
	arvoreB * filhos [ MAX FILHOS ];
};

void insere chave ( arvoreB *raiz , int info , arvoreB * filhodir ) {
	int k, pos;

// obtem o endereco para insercao da nova chave
	pos = busca binaria ( raiz , info );
	k = raiz->num chaves;

// libera espaco para insercao da chave na pagina
	while( k > pos && info < raiz->chaves[ k - 1 ] ) {
		raiz ->chaves[ k ] = raiz->chaves[ k - 1 ];
		raiz ->filhos[ k + 1 ] = raiz->filhos[ k ];
		k--;
	}

// insere a chave
	raiz ->chaves[ pos ] = info;
	raiz ->filhos[ k + 1 ] = filhodir ;
	raiz ->num chaves++;
}

arvoreB* insere ( arvoreB *raiz, int info , bool *h, int *info retorno ) {
	int i , j , pos, info mediano;
	arvoreB *temp, *filho dir ;

	if ( ! raiz ) {
		*h = true; // atingiu no folha
		*info retorno = info;
		return NULL;
	} else {
		pos = busca binaria ( raiz , info );
		if ( raiz->num chaves > pos && raiz->chaves[ pos ] == info ) {
			printf ( ”Chave ja contida na arvore ” );
			*h = false;
		} else {
			filho dir = insere( raiz->filhos[ pos ], info , h, info retorno );
			if ( *h ) {
				if ( raiz->num chaves < MAX CHAVES ) { // tem espaco na pagina
					insere chave ( raiz , *info retorno , filho dir );
					*h = false;
				} else { // overflow ! SPLIT-AND-PROMOTE
					temp = ( arvoreB* ) malloc( sizeof ( arvoreB ) );
					temp->num chaves = 0;
					for ( i = 0; i < MAX FILHOS; i++ )
						temp->filhos[ i ] = NULL;

					info mediano = raiz->chaves[ MIN OCUP ]; // PROMOTE

// insere metade da pagina no temp (SPLIT)
					temp->filhos[ 0 ] = raiz->filhos[ MIN OCUP + 1 ];
					for ( i = MIN OCUP + 1; i < MAX CHAVES; i++ )
						insere chaves ( temp, raiz->chaves[ i ], raiz->filhos[ i + 1 ] );

// atualiza raiz
					for ( i = MIN OCUP; i < MAX CHAVES; i++ ) {
						raiz->chaves[ i ] = 0;
						raiz->filhos[ i + 1 ] = NULL;
					}
					raiz->num chaves = MIN OCUP;

// verifica onde inserir a nova chave
					if ( pos <= MIN OCUP )
						insere chave ( raiz , *info retorno , filho dir );
					else
						insere chave ( temp, *info retorno , filho dir );

					*info retorno = info mediano;
					return temp;
				}
			}
		}
	}
}


arvoreB * insere arvoreB ( arvoreB *raiz , int info ) {
	bool h;
	int info retorno , i ;
	arvoreB * filho dir , *nova raiz ;

	filho dir = insere( raiz , info , &h, &info retorno );
	if ( h ) { // aumenta altura da arvore ?
		nova raiz = ( arvoreB* ) malloc( sizeof ( arvoreB ));
		nova raiz ->num chaves = 1;
		nova raiz->chaves[ 0 ] = info retorno ;
		nova raiz->filhos[ 0 ] = raiz;
		nova raiz->filhos[ 1 ] = filho dir ;

		for ( i = 2; i <= MAX CHAVES; i++ )
			nova raiz->filhos[ i ] = NULL;
		return nova raiz ;
	} else return raiz ;
}


int busca binaria ( arvoreB *no, int info ) {
	int meio, i = 0, f = no->num chaves - 1;

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
		pos = busca binaria( no, info );
		if ( pos < no->num chaves && no->chaves[ pos ] == info )
			return no;
		else
			no = no->filhos[ pos ];
	}
	return NULL;
}


void em ordem( arvoreB *raiz ) {
	int i ;

	if ( raiz ) {
		for ( i = 0; i < raiz->num chaves; i++ ) {
			em ordem( raiz->filhos[ i ] );
			printf ( ”\n%d”, raiz->chaves[ i ] );
		}
		em ordem( raiz->filhos[ i ] );
	}
}


