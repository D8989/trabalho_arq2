#include <stdio.h>
#include "memoriaPrincipal.h"
#include "memoriaCacheConjunto.h"

#define TESTES 20

//Apenas para testes
void printDados(int *v){
	int i;
	printf("\t\t\tDados: ");
	for(i = 0; i < PALAVRAS; ++i){
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main(){

	CONJUNTO mCache[CONJUNTOS];
	initCache(mCache);
	initFifo(mCache);

	int *mPrincipal = alocaMP();
	initMP(mPrincipal);

	int hit = 0, miss = 0;
	uint32_t endereco[TESTES] = {0, 8, 16, 32,0,5,45,7,2,36,69,54,14,21,15,87,74,56,55,66};
	int palavra;
	int dados[PALAVRAS];
	int i;
	for(i = 0; i < TESTES; ++i){
		printf("endereco = %d; tag = %d; Conjunto = %d;\n", endereco[i], tagEndereco(endereco[i]), endConjunto(endereco[i]));

		if( lerPalavraCache(mCache, endereco[i], &palavra) ){
			printf("PALAVRA = %d\n", palavra);
			hit++;
		}else{
			lerPalavras(mPrincipal, endereco[i], dados, PALAVRAS, fatoracao(PALAVRAS));
			printDados(dados);
			escreverCache(mCache, endereco[i], dados);
			miss++;
		}
		printCache(mCache);
	}
	
	printf("hit = %d\n", hit);
	printf("miss = %d\n", miss);

	
	desalocaMP(mPrincipal);

	return 0;
}