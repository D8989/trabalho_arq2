#include "memoriaCacheConjunto.h"
#include <stdio.h>
#include <stdlib.h>

void initCache(CONJUNTO *cache)
{
	int i, j;
	for(i = 0; i < CONJUNTOS; ++i){
		for(j = 0; j < BLOCOS; ++j){
			cache[i].bloco[j].bitValidade = 0;
			cache[i].bloco[j].tag = -1;
		}
	}
}
// inicia a função de troca FIFO 
void initFifo(CONJUNTO *cache)
{
	int i, j;
	for(i = 0; i < CONJUNTOS; ++i){
		cache[i].bloco[0].controle = 1;
		for(j = 1; j < BLOCOS; j++){
			cache[i].bloco[j].controle = 0;
		}
	}
}

//inicia o bit de controle - LRU
void initLRU(CONJUNTO *cache)
{
	int i, j;
	int cont;
	for(i = 0; i < CONJUNTOS; ++i){
		cont = 1;
		cache[i].bloco[0].controle = cont;
		for(j = 1; j < BLOCOS; j++){
			cont++;
			cache[i].bloco[j].controle = cont;
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
int bitValidade(CONJUNTO *cache, int c, int b)
{
	return cache[c].bloco[b].bitValidade;
}

// retorna a tag do bloco
int tagBloco(CONJUNTO *cache, int c, int b)
{
	return cache[c].bloco[b].tag;
}

// retorna 1 se o endereco foi encontrada, a 'palavra' recebe o dado requisidado
int lerPalavraCache(CONJUNTO *cache, uint32_t endereco, int *palavra)
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
				*palavra = cache[c].bloco[bloco].palavra[p];
				return 1;
			}
		}else{
			return 0; //bloco vazio encontrado
		}
	}
	return 0; //bloco cheio
}

// retorna 1 se o endereco foi encontrada, a 'palavra' recebe o dado requisidado, atualiza o lru
int lerPalavraCacheLRU(CONJUNTO *cache, uint32_t endereco, int *palavra)
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
				*palavra = cache[c].bloco[bloco].palavra[p];
				atualizarLRU(cache, c, bloco);
				return 1;
			}
		}else{
			return 0; //bloco vazio encontrado
		}
	}
	return 0; //bloco cheio
}

// escreve o conjunto de palavras na cache
void escreverCache(CONJUNTO *cache, uint32_t endereco, int *dados)
{
	int i;
	int c = endConjunto(endereco);
	int b = procuraBloco(cache, c);
	int tag = tagEndereco(endereco);

	if(b < 0){
		b = proxBlocoSair(cache, c);
		atualizarFifo(cache, c);
	}
	for(i = 0; i < PALAVRAS; ++i){
		cache[c].bloco[b].palavra[i] = dados[i];
	}

	cache[c].bloco[b].bitValidade = 1;
	cache[c].bloco[b].tag = tag;
}

// escreve o conjunto de palavras na cache
void escreverCacheLRU(CONJUNTO *cache, uint32_t endereco, int *dados)
{
	int i;
	int c = endConjunto(endereco);
	int b = procuraBloco(cache, c);
	int tag = tagEndereco(endereco);

	if(b < 0){ //Cache está cheia
		b = proxBlocoSair(cache, c);
	}
	for(i = 0; i < PALAVRAS; ++i){
		cache[c].bloco[b].palavra[i] = dados[i];
	}

	cache[c].bloco[b].bitValidade = 1;
	cache[c].bloco[b].tag = tag;
	atualizarLRU(cache, c, b);
}

//retorna 1 se todos os blocos do conjunto c estiverem cheios
int procuraBloco(CONJUNTO *cache, int c)
{
	int b;
	for(b = 0; b < BLOCOS; ++b){
		if(cache[c].bloco[b].bitValidade == 0){
			return b;
		}
	}
	return -1;
}



int proxBlocoSair(CONJUNTO *cache, int c)
{
	int b = 0;
	while(cache[c].bloco[b].controle != 1){
		b++;
	}
	return b;
}

void atualizarFifo(CONJUNTO *cache, int c)
{
	int b = 0;
	while(cache[c].bloco[b].controle != 1){
		b++;
	}
	cache[c].bloco[b].controle = 0;
	if(b == BLOCOS-1){
		cache[c].bloco[0].controle = 1;//volta pro inicio do bloco
	}else{
		b++;
		cache[c].bloco[b].controle = 1;
	}
}

//atualiza a LRU do conjunto c
void atualizarLRU(CONJUNTO *cache, int c, int b)
{
	int i;
	int aux = cache[c].bloco[b].controle;
	for(i = 0; i < BLOCOS; ++i){
		if(i == b){
			cache[c].bloco[i].controle = MAIS_RECENTE;
		}else
		if(cache[c].bloco[i].controle >= aux){
			cache[c].bloco[i].controle -= 1;
		}
	}
}

//imprime a cache na tela
void printCache(CONJUNTO *cache)
{
	int c,b,p;
	for(c = 0; c < CONJUNTOS; c++){
		printf("\tConjunto %d:*******************************\n", c);
		for(b = 0; b < BLOCOS; b++){
			printf("\t|\tBloco %d ---------------------------\n", b);
			if(cache[c].bloco[b].bitValidade == 0){
				printf("\t|\t\tVAZIO\n");
				//printf("\t|\t\tCONTROLE = %d\n",cache[c].bloco[b].controle);
			}else{
				printf("\t|\t\tTAG = %d\n",cache[c].bloco[b].tag);
				printf("\t|\t\tCONTROLE = %d\n",cache[c].bloco[b].controle);
				for(p = 0; p < PALAVRAS; p++){
					printf("\t|\t\t\tword %d: %d\n", p,cache[c].bloco[b].palavra[p]);

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
void printControle(CONJUNTO *cache)
{
	int i,j;
	for(i = 0; i < CONJUNTOS; i++){
		printf("\t\t\tConjunto %d\n", i);
		for(j = 0; j < BLOCOS; j++){
			printf("\t\t\t\tBloco %d: \n",j);
			printf("\t\t\t\t\tControle: %d\n",cache[i].bloco[j].controle);
			printf("\t\t\t\t\tValidade: %d\n",cache[i].bloco[j].bitValidade);
			printf("\t\t\t\t\tTAG: %d\n",cache[i].bloco[j].tag);
		}
	}
}