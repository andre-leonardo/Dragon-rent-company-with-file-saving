#include <stdio.h>
typedef struct {
	int codigo;
	char nome[30];
	int idade;
	float valor;
	int unidade;
	int codigoElemento;
	int checarLocacao;
	char elemento[30];
} Dragao;

FILE* drag;


int inicializarDragoes();
int encerraDragoes();
int salvarDragao(Dragao c);
int QuantidadeDragoes();
Dragao* obterDragaoPeloIndice(int indice);
Dragao* obterDragaoPeloCodigo(int codigo);
Dragao* obterDragaoPeloNome (char* nome);
int ApagarDragaoPeloCodigo(int codigo);
int atualizarDragao(int mudancaInt, char* mudanca, int m,int opcao,int codigo);
int registrarMudancaDrag(int qtd, int cod);
int registrarLocacaoDrag(int cod, int aumentarOuDiminuir);

