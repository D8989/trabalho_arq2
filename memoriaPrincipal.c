//	Nome: 	Daniel Juventude Moreira
//			Vitoria
//	corpo das funções sobre a memoria principal
//	e funções basicas

#include <stdio.h>
#include <stdlib.h>
#include "memoriaPrincipal.h"

int* alocaMP(){
	int *mem = (int*)malloc(sizeof(int)*TAMANHO_MP);
	if(mem == NULL){
		msgErrorMP("Não foi possivel alocar a memoria principal");
	}
	return mem;
}

void desalocaMP(int *mp){
	free(mp);
}

int retornaPalavraMP(int *mp, uint32_t end){
	int i = 0;
	while(i < TAMANHO_MP && i < end){
		++i;
	}
	if(i == TAMANHO_MP){
		msgErrorMP("endereço fora do limite da memoria principal.");
	}
	return mp[i];
}

void lerPalavras(int *mp, uint32_t end, int *palavras, int n, int offset)
{
	int i = 0;
	int j;
	int tag = end >> offset;
	int tagAux;
	while(i < TAMANHO_MP){
		tagAux = i >> offset;
		if(tagAux == tag){
			for(j = 0; j < n; ++j, ++i){
				palavras[j] = mp[i];
			}
			i = TAMANHO_MP;
		}
		i += n;
	}
	if(i == TAMANHO_MP){
		msgErrorMP("endereço fora do limite da memoria principal.");
	}
}

void initMP(int *mp){
	int i;
	for(i = 0; i < TAMANHO_MP; ++i){
		mp[i] = 2*i;
	}
}

void msgErrorMP(const char *msg){
	printf("\tERROR: memoria Principal:\n");
	puts(msg);
	exit(-1);
}