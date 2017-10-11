//	Nome: 	Daniel Juventude Moreira
//			Vitoria
#ifndef MEMORIA_CACHE_H
#define MEMORIA_CACHE_H value

#include <stdint.h>

#define NUM_BLOCOS 	8
#define NUM_PALAVRA 4
#define LINHA NUM_PALAVRA+2 
#define ID_TAG LINHA-1	//ultima linha é a tag (rotulo)
#define ID_VALIDADE LINHA-2	//penultima linha é o bit de validade

//typedef uint32_t endereco;

int** alocaCache();
void initCache(int **cache);
void desalocaCache(int **cache);
int bitValidade(int *bloco); //retorna o bit de validade do bloco
int tagBloco(int *bloco); //retorna a tag do bloco
void escreveCache(int **cache, uint32_t end, int *palavra); //escreve as palavras no bloco
int lerPalavraCache(int **cache, uint32_t end, int *palavra); //retorna 1 se achou a palavra, 0 se não encoutrou
uint32_t indiceBloco(uint32_t end); //retorna o endereço da cache
uint32_t indicePalavra(uint32_t end);
int retornaTag(uint32_t end); //retorna a tag do endereço
int fatoracao(int a);
void msgErrorCache(const char *msg);
void printCache(int **cache);

#endif