#include "memoriaCache.h"
#include <math.h>


int** alocaCache()
{
	if( NUM_BLOCOS%2 != 0){
		msgErrorCache("\t\tNumero de blocos não é multiplo por dois.");
	}
	if(NUM_PALAVRA%2 != 0){
		msgErrorCache("\t\tNumero de palavras não é multiplo de dois.");
	}

	int **cache = (int**)malloc(sizeof(int*)*NUM_BLOCOS);
	if(cache == NULL){
		msgErrorCache("\t\tError ao alocar o número de blocos da cache.");
	}
	int i;
	for(i = 0; i < NUM_BLOCOS; ++i){
		cache[i] = (int*)malloc(sizeof(int)*LINHA);
		if( cache[i] == NULL){
			msgErrorCache("\t\tError ao alocar a linha da cache");
		}
	}
	return cache;
}

void desalocaCache(int **cache)
{
	int i;
	if(cache != NULL){
		for(i = 0; i < LINHA && cache[i] != NULL; ++i){
			free(cache[i]);
		}
		free(cache);
	}

}

int bitValidade(int *bloco)
{
	return bloco[ID_VALIDADE];
}

int tag(int *bloco)
{
	return bloco[ID_TAG];
}

int retornaDado(int **cache, endereco end)
{

}

int indiceBloco(endereco end)
{
	int desloca = fatoracao(NUM_PALAVRA);
	end = end >> desloca;

	return endr%NUM_BLOCOS;
}

int indicePalavra(endereco end)
{
	int desloca = fatoracao(NUM_PALAVRA);
	end = end << 32-desloca;
	end = end >> 32-desloca;
}

int fatoracao(int a)
{
	int cont;
	for(cont = 0; a != 1; cont++){
		a /= 2;
	}
	return cont;
}

void msgErrorCache(const char *msg)
{
	printf("\tERROR: memoria Cache:\n");
	puts(msg);
	exit(-1);
}