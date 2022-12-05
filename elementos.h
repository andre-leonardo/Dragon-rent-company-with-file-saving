#include <stdio.h>
typedef struct {
	int codigo;
	char nome[30];
	char vulnerabilidade[30];
} Elemento;

FILE* elem;
int retornaTamanhoElementos();
int inicializarElementos();
int encerraElementos();
int salvarElemento(Elemento c);
int QuantidadeElementos();
Elemento* obterElementoPeloIndice(int codigo);
Elemento* obterElementoPeloCodigo(int codigo);
Elemento* obterElementoPeloNome (char* nome);
int atualizarElemento(Elemento* e, int codigo);
int ApagarElementoPeloCodigo(int codigo);
