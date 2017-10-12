Trabalho de arq 2;
	Simulação de mapeamento de memoria entra a cache e a memoria principal. Mapeamento Direto

Modificar a cache:
	Para modificar o numero de blocos e o numero de palavras no bloco,
	Modifique as canstantes NUM_BLOCOS e NUM_PALAVRA.
	NUM_BLOCOS e NUM_PALAVRA devem conter valores multiplos de 2, mas NUM_BLOCOS e NUM_PALAVRA podem ser iguais à 1.

para compilar o de cache Direto:
	gcc memoriaCacheDireto.c memoriaPrincipal.c mainDireto.c

para compilar o de cache por conjunto:
	gcc memoriaCacheDireto.c memoriaPrincipal.c mainConjunto.c

OBS:
	os arquivos *.c e *.h devem estar na mesma pagina