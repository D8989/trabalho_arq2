//	Nome: 	Daniel Juventude Moreira
//			Vitoria
#include <stdio.h>
#include "memoriaCacheDireto.h"
#include "memoriaPrincipal.h"

#define TESTES 6 //quantidade de casos de testes

void printDados(int *v){
	int i;
	printf("\t\t\tDados: ");
	for(i = 0; i < NUM_PALAVRA; ++i){
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main(){
	int *mPrincipal = alocaMP();
	initMP(mPrincipal);

	int **mCache = alocaCache();
	initCache(mCache);

	int hit = 0, miss = 0;
	uint32_t endereco[TESTES] = {30, 25, 115, 31, 114, 24};
	int palavra;
	int dados[NUM_PALAVRA];
	int i;
	for(i = 0; i < TESTES; ++i){
		printf("endereco = %d; tag = %d; id bloco = %d;\n", endereco[i], retornaTag(endereco[i]), indiceBloco(endereco[i]));

		if( lerPalavraCache(mCache, endereco[i], &palavra) ){
			printf("PALAVRA = %d\n", palavra);
			hit++;
		}else{
			lerPalavras(mPrincipal, endereco[i], dados, NUM_PALAVRA, fatoracao(NUM_PALAVRA));
			printDados(dados);
			escreveCache(mCache, endereco[i], dados);
			miss++;
		}
		printCache(mCache);
	}
	
	printf("hit = %d\n", hit);
	printf("miss = %d\n", miss);

	desalocaCache(mCache);
	desalocaMP(mPrincipal);

	return 0;
}