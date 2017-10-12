#include "memoriaCacheConjunto.h"
#include <stdio.h>
#include <stdlib.h>

int*** alocaCache()
{
	if(CONJUNTOS%2 != 0 && CONJUNTOS != 1){
		msgErrorCache("número de conjuntos não é multiplo de 2.");
	}
	if(PALAVRAS%2 != 0 && PALAVRAS != 1){
		msgErrorCache("número de palavras por bloco não é multiplo de dois.");
	}
	int i, j;

	int*** cache = (int***)malloc(sizeof(int**)*CONJUNTOS);
	if(cache == NULL){
		msgErrorCache("não foi possivel alocar a memoria para os conjuntos.");
	}
	
	for(i = 0; i < CONJUNTOS; ++i){
		cache[i] = (int**)malloc(sizeof(int*)*BLOCOS);
		if(cache[i] == NULL){
			msgErrorCache("não foi possivel alocar a memoria para os blocos.");
		}

		for(j = 0; j < BLOCOS; ++j){
			cache[i][j] = (int*)malloc(sizeof(int)*LINHA);
			if(cache[i][j] == NULL){
				msgErrorCache("Não foi possivel alocar a memoria para as palavras.");
			}
		}
	}

	return cache;
}

void desalocaCache(int ***cache)
{
	int i, j;
	for(i = 0; i < CONJUNTOS; ++i){
		for(j = 0; j < BLOCOS; ++j){
			free(cache[i][j]);
		}
		free(cache[i]);
	}
	free(cache);
}

void initCache(int ***cache)
{
	int i, j;
	for(i = 0; i < CONJUNTOS; ++i){
		for(j = 0; j < BLOCOS; ++j){
			cache[i][j][ID_VALIDADE] = 0;
			cache[i][j][ID_TAG] = -1;
		}
	}
}

void initFifo(int ***cache)
{
	int i, j;

	for(i = 0; i < CONJUNTOS; ++i){
		cache[i][0][ID_CONTROLE] = 1;
		for(j = 1; j < BLOCOS; j++){
			cache[i][j][ID_CONTROLE] = 0;
		}
	}
}

//retorna o endereco do conjunto
uint32_t endConjunto(uint32_t end)
{
	end = end >> fatoracao(PALAVRAS); //desconsidera os bits da palavra
	return end%CONJUNTOS;
}

//retorna o endereco da palavra procurada
uint32_t endPalavra(uint32_t endereco)
{
	return endereco%PALAVRAS;
}

//retorna a tag do endereco
uint32_t tagEndereco(uint32_t endereco)
{
	int offset = fatoracao(PALAVRAS);
	offset += fatoracao(CONJUNTOS);
	endereco = endereco >> offset;
	return endereco;
}

// retorna o bit validade do bloco
int bitValidade(int ***cache, int c, int b)
{
	return cache[c][b][ID_VALIDADE];
}

// retorna a tag do bloco
int tagBloco(int ***cache, int c, int b)
{
	return cache[c][b][ID_TAG];
}

// retorna 1 se o endereco foi encontrada, a 'palavra' recebe o dado requisidado
int lerPalavraCache(int ***cache, uint32_t endereco, int *palavra)
{
	int c = endConjunto(endereco);
	int t = tagEndereco(endereco);
	int p = endPalavra(endereco);
	int bloco;
	for(bloco = 0; bloco < BLOCOS; ++bloco){
		int validade = bitValidade(cache, c, bloco);
		if(validade == 1){
			int tag = tagBloco(cache, c, bloco);
			if(tag == t){
				*palavra = cache[c][bloco][p];
				return 1;
			}
		}else{
			return 0; //bloco vazio
		}
	}
	return 0;
}

// escreve o conjunto de palavras na cache
void escreverCache(int ***cache, uint32_t endereco, int *dados)
{
	int i;
	int c = endConjunto(endereco);
	int b = procuraBloco(cache, c);
	int tag = tagEndereco(endereco);
	if(b < 0){
		b = proxBlocoSair(cache, c);
		for(i = 0; i < PALAVRAS; ++i){
			cache[c][b][i] = dados[i];
		}
		atualizarFifo(cache, c);
		//cache[c][b][ID_VALIDADE] = 1;
	}else{
		//printf("b = %d\n", b);
		for(i = 0; i < PALAVRAS; ++i){
			//printf("dados[%d] = %d\n",i, dados[i]);
			cache[c][b][i] = dados[i];
		}
		//cache[c][b][ID_VALIDADE] = 1;
	}
	cache[c][b][ID_VALIDADE] = 1;
	cache[c][b][ID_TAG] = tag;
}

//retorna 1 se todos os blocos do conjunto c estiverem cheios
int procuraBloco(int ***cache, int c)
{
	int b;
	for(b = 0; b < BLOCOS; ++b){
		if(cache[c][b][ID_VALIDADE] == 0){
			return b;
		}
	}
	return -1;
}



int proxBlocoSair(int ***cache, int c)
{
	int b = 0;
	while(cache[c][b][ID_CONTROLE] != 1){
		b++;
	}
	return b;
}

void atualizarFifo(int ***cache, int c)
{
	int b = 0;
	while(cache[c][b][ID_CONTROLE] != 1){
		b++;
	}
	cache[c][b][ID_CONTROLE] = 0;
	if(b == BLOCOS-1){
		cache[c][0][ID_CONTROLE] = 1;
	}else{
		b++;
		cache[c][b][ID_CONTROLE] = 1;
	}
}

//imprime a cache na tela
void printCache(int ***cache)
{
	int c,b,p;
	for(c = 0; c < CONJUNTOS; c++){
		printf("\tConunto %d:\n", c);
		for(b = 0; b < BLOCOS; b++){
			printf("\t\tBloco %d\n", b);
			if(cache[c][b][ID_VALIDADE] == 0){
				printf("\t\t\tVAZIO\n");
			}else{
				printf("\t\t\tTAG = %d\n", cache[c][b][ID_TAG]);
				printf("\t\t\tCONTROLE = %d\n", cache[c][b][ID_CONTROLE]);
				for(p = 0; p < PALAVRAS; p++){
					printf("\t\t\t\tword %d: %d\n", p, cache[c][b][p]);
				}
			}
		}
	}
}

void msgErrorCache(const char *msg)
{
	printf("\tERROR: memoria Cache:\n");
	puts(msg);
	exit(-1);
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


//TESTE
void printControle(int ***cache)
{
	int i,j;
	for(i = 0; i < CONJUNTOS; i++){
		printf("\t\t\tConjunto %d\n", i);
		for(j = 0; j < BLOCOS; j++){
			printf("\t\t\t\tBloco %d: \n",j);
			printf("\t\t\t\t\tControle: %d\n", cache[i][j][ID_CONTROLE]);
			printf("\t\t\t\t\tValidade: %d\n", cache[i][j][ID_VALIDADE]);
			printf("\t\t\t\t\tTAG: %d\n", cache[i][j][ID_TAG]);
		}
	}
}