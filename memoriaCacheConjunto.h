#ifndef MEMORIA_CACHE_CONJUNTO_H
#define MEMORIA_CACHE_CONJUNTO_H value

#include <stdint.h>

#define CONJUNTOS 	2
#define BLOCOS 		4
#define PALAVRAS 	4
#define LINHA 		PALAVRAS+3 //bit validade, tag, controle
#define ID_CONTROLE LINHA-1 //ultimo elemento da linha
#define ID_TAG 		LINHA-2 //penultimo elemento da linha
#define ID_VALIDADE LINHA-3 //ante-penultimo elemento da linha

#define MAIS_RECENTE BLOCOS;

typedef struct{
	int palavra[PALAVRAS];
	int bitValidade;
	int tag;
	int controle;
}BLOCO;

typedef struct{
	BLOCO bloco[BLOCOS];
}CONJUNTO;

//inicia a cache
void initCache(CONJUNTO *cache);

// retorna o bit validade do bloco b do conjunto c
int bitValidade(CONJUNTO *cache, int c, int b);
// retorna a tag do bloco b do conjunto c
int tagBloco(CONJUNTO *cache, int c, int b);
//retorna o endereco do conjunto
uint32_t endConjunto(uint32_t endereco);
//retorna o endereco da palavra
uint32_t endPalavra(uint32_t endereco);
//retorna a tag do endereco
uint32_t tagEndereco(uint32_t endereco);

// retorna 1 se o endereco foi encontrada, a 'palavra' recebe o dado requisidado
int lerPalavraCache(CONJUNTO *cache, uint32_t endereco, int *palavra);
// retorna 1 se o endereco foi encontrada, a 'palavra' recebe o dado requisidado, atualiza o lru
int lerPalavraCacheLRU(CONJUNTO *cache, uint32_t endereco, int *palavra);
// escreve o conjunto de palavras na cache
void escreverCache(CONJUNTO *cache, uint32_t endereco, int *dados);
// escreve o conjunto de palavras na cache
void escreverCacheLRU(CONJUNTO *cache, uint32_t endereco, int *dados);
//retorna o indice do primeiro bloco vazio, ou -1 se o bloco do conjunto c estiver cheio
int procuraBloco(CONJUNTO *cache, int c);
//int procuraBloco(int ***cache, int c);

//inicia o bit de controle - FIFO
void initFifo(CONJUNTO *cache);
//retorna o indice do prox bloco a sair da cache do conjunto c
int proxBlocoSair(CONJUNTO *cache, int c);
//atualiza a FIFO do conjunto c
void atualizarFifo(CONJUNTO *cache, int c);

//inicia o bit de controle - LRU
void initLRU(CONJUNTO *cache);
//atualiza a LRU do conjunto c
void atualizarLRU(CONJUNTO *cache, int c, int b);


//imprime a cache na tela
void printCache(CONJUNTO *cache);
//TESTE
void printControle(CONJUNTO *cache);


int fatoracao(int a);
void msgErrorCache(const char *msg);

#endif