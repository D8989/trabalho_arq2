#ifndef MEMORIA_CACHE_H
#define MEMORIA_CACHE_H value

#define NUM_BLOCOS 	8
#define NUM_PALAVRA 4
#define LINHA NUM_PALAVRA+2 
#define ID_TAG LINHA-1	//ultima linha é a tag (rotulo)
#define ID_VALIDADE LINHA-2	//penultima linha é o bit de validade

typedef uint32_t endereco;

int** alocaCache();
void desalocaCache(int **cache);
int bitValidade(int *bloco);
int tag(int *bloco);
int retornaDado(int *cache, endereco end);
int indiceBloco(endereco end);
int indicePalavra(endereco end); //CONTINUAR AQUI
int fatoracao(int a);
void msgErrorCache(const char *msg);

#endif