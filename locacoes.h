#include <stdio.h>
typedef struct {
	int codigoLocacao;
	int codigoGuerreiroLocador;
	int codigoDragaoLocado;
	int quantidadeLocada;
	int locacaoNaoDevolvida;
	float valorDiario;
	char dataInicio[30];
	char dataFim[30];
} Locacao;
FILE* loca_tmp;
FILE* loca;

int inicializarLocacoes();
int encerraLocacoes();
int salvarLocacao(Locacao c, int codDrag, int codGuerr, int qtd);
int QuantidadeLocacoes();
Locacao* obterLocacaoPeloIndice(int codigoLocacao);
Locacao* obterLocacaoPeloCodigo(int codigoLocacao);
int DevolverLocacaoPeloCodigo(int codigo);
int ExcluirLocacao(int codigo);
int atualizarLocacao(char* mudanca, int m, int opcao, int codigo);
