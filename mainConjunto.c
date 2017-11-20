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
	//initFifo(mCache); 	//desmonete essa linha pra usar a FIFO
	initLRU(mCache);	//desmonete essa linha pra usar a LRU

	int *mPrincipal = alocaMP();
	initMP(mPrincipal);

	int *mPrincipal = alocaMP();
	initMP(mPrincipal);

	int hit = 0, miss = 0;
	uint32_t endereco[TESTES] = {0, 8, 16, 32,0,5,45,7,2,120,69,11,14,2,15,87,5,56,55,127};

	int palavra;
	int dados[PALAVRAS];
	int i;
	int flag;
	for(i = 0; i < TESTES; ++i){
		printf("endereco = %d; tag = %d; Conjunto = %d;\n", endereco[i], tagEndereco(endereco[i]), endConjunto(endereco[i]));
		//flag = lerPalavraCache(mCache, endereco[i], &palavra); //FIFO
		flag = lerPalavraCacheLRU(mCache, endereco[i], &palavra);//LRU
		if( flag ){
			printf("PALAVRA = %d\n", palavra);
			hit++;
		}else{
			lerPalavras(mPrincipal, endereco[i], dados, PALAVRAS, fatoracao(PALAVRAS));
			printDados(dados);
			//escreverCache(mCache, endereco[i], dados);	//FIFO
			escreverCacheLRU(mCache, endereco[i], dados);	//LRU
			miss++;
		}
		printCache(mCache);
	}
	
	printf("hit = %d\n", hit);
	printf("miss = %d\n", miss);

	
	desalocaMP(mPrincipal);

	return 0;
}
