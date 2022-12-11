#include <stdio.h>
typedef struct {
	int codigo;
	int checarLocacao;
	char nome[30];
	char reino[30];
	char titulo[30];
} Guerreiro;




int inicializarGuerreiros();
int encerraGuerreiros();
int salvarGuerreiro(Guerreiro c);
int QuantidadeGuerreiros();
Guerreiro* obterGuerreiroPeloIndice(int indice);
Guerreiro* obterGuerreiroPeloCodigo(int codigo);
Guerreiro* obterGuerreiroPeloNome (char* nome);
int ApagarGuerreiroPeloCodigo(int codigo);
int atualizarGuerreiro(Guerreiro* g,int codigo);
int registrarLocacaoGuerr(int cod, int aumentarOuDiminuir);

