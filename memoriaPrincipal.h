//	Nome: 	Daniel Juventude Moreira
//		Vitoria
//	escobo das funções sobre a memoria principal
//	e funções basicas

#ifndef MEMORIA_PRINCIPAL_H
#define MEMORIA_PRINCIPAL_H value

#include <stdint.h>

#define TAMANHO_MP 100 //tamanho da memoria principal

typedef uint32_t endereco; // para que o int tenha exatamente 32 bits, e que não mostre valores negativos

int* 	alocaMP();	//aloca o vetor
void 	desalocaMP(int *mp);
int 	retornaPalavra(int *mp, endereco end); 
void	encherMP(int *mp); //inicializa o vetor com valores "aleatorios"
void	msgErrorMP(const char *msg);// imprime a mensagem de erro e fecha o programa

#endif