//	Nome: 	Daniel Juventude Moreira
//		Vitoria
//	corpo das funções sobre a memoria principal
//	e funções basicas

#include <stdio.h>
#include <stdlib.h>
#include "memoriaPrincipal.h"

int* alocaMP(){
	int *mem = (int*)malloc(sizeof(int)*TAMANHO_MP);
	if(mem == NULL){
		msgError("Não foi possivel alocar a memoria principal");
	}
	return mem;
}

void desalocaMP(int *mp){
	free(mp);
}

int retornaPalavra(int *mp, endereco end){
	int i = 0;
	while(i < TAMANHO_MP && i < end){
		++i;
	}
	if(i == TAMANHO_MP){
		msgError("endereço fora do limite da memoria principal.");
	}
	return mp[i];
}

void encherMP(int *mp){
	int i;
	for(i = 0; i < TAMANHO_MP; ++i){
		mp[i] = 2*i;
	}
}

void msgError(const char *msg){
	puts(msg);
	exit(-1);
}