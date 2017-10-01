//	Nome: 	Daniel Juventude Moreira
//			Vitoria
#include "memoriaCacheDireto.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int** alocaCache()
{
	if( NUM_BLOCOS%2 != 0 && NUM_BLOCOS != 1){
		msgErrorCache("\t\tNumero de blocos não é multiplo por dois.");
	}
	if(NUM_PALAVRA%2 != 0 && NUM_PALAVRA != 1){
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

void initCache(int **cache)
{
	int i;
	for(i = 0; i < NUM_BLOCOS; ++i){
		cache[i][ID_VALIDADE] = 0;
		cache[i][ID_TAG] = 0;
	}
}

int bitValidade(int *bloco)
{
	return bloco[ID_VALIDADE];
}

int tagBloco(int *bloco)
{
	return bloco[ID_TAG];
}

void escreveCache(int **cache, uint32_t end, int *palavra)
{
	uint32_t bloco = indiceBloco(end);
	int tag = retornaTag(end);
	int i;

	cache[bloco][ID_TAG] = tag;
	cache[bloco][ID_VALIDADE] = 1;

	for(i = 0; i < NUM_PALAVRA; i++){
		cache[bloco][i] = palavra[i];
	}
}

int lerPalavraCache(int **cache, uint32_t end, int *palavra)
{
	uint32_t endBloco = indiceBloco(end);
	int tag = retornaTag(end);
	uint32_t endPalavra = indicePalavra(end);

	if( bitValidade(cache[endBloco]) == 1){
		if( tagBloco(cache[endBloco]) == tag){
			*palavra = cache[endBloco][endPalavra];
			printf("\t\tPALAVRA ENCONTRADA : %d\n", *palavra );
			return 1;
		}
	}
	return 0;
}

uint32_t indiceBloco(uint32_t end)
{
	end = end >> fatoracao(NUM_PALAVRA); //desconsidera os bits da palavra
	return end%NUM_BLOCOS;
}

uint32_t indicePalavra(uint32_t end)
{
	return end%NUM_PALAVRA; // os bits mais significativos
}

int retornaTag(uint32_t end)
{
	int offset = fatoracao(NUM_PALAVRA);
	offset += fatoracao(NUM_BLOCOS);
	end = end >> offset;
	return end;
}	

int fatoracao(int a)
{
	int cont = 0;
	while(a != 1){
		a /= 2;
		cont++;
	}
	return cont;
}

void msgErrorCache(const char *msg)
{
	printf("\tERROR: memoria Cache:\n");
	puts(msg);
	exit(-1);
}

void printCache(int **cache)
{
	int i, j;
	for(i = 0; i < NUM_BLOCOS; ++i){
		printf("Bloco %d; bitVal = %d; tag = %d\n", i, cache[i][ID_VALIDADE], cache[i][ID_TAG]);
		if(cache[i][ID_VALIDADE] == 1){
			for(j = 0; j < NUM_PALAVRA; ++j){
				printf("\tword %d: %d;\n", j, cache[i][j]);
			}
			printf("\n\n");
		}else{
			printf("\tVAZIO\n");
		}
	}
	printf("\n");
	printf("'''''''''''''''''''''''''''''''''''''''''\n");
}