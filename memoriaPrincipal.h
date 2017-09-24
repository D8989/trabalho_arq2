//	Nome: 	Daniel Juventude Moreira
//		Vitoria
//	escobo das funções sobre a memoria principal
//	e funções basicas

#ifndef MEMORIA_PRINCIPAL_H
#define MEMORIA_PRINCIPAL_H value

#define TAMANHO_MP 100 //tamanho da memoria principal

typedef unsigned int endereco;

int* 	alocaMP();	//aloca o vetor
void 	desalocaMP(int *mp);
int 	retornaPalavra(int *mp, endereco end); 
void	encherMP(int *mp); //inicializa o vetor com valores "aleatorios"
void	msgError(const char *msg);// imprime a mensagem de erro e fecha o programa

#endif