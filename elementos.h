typedef struct {
	int codigo;
	char nome[30];
	char vulnerabilidade[30];
} Elemento;


int retornaTamanhoElementos();
int inicializarElementos();
int encerraElementos();
int salvarElemento(Elemento c);
int QuantidadeElementos();
Elemento* obterElementoPeloIndice(int codigo);
Elemento* obterElementoPeloCodigo(int codigo);
Elemento* obterElementoPeloNome (char* nome);
int atualizarElemento(char* mudanca, int m,int opcao,int codigo);
int ApagarElementoPeloCodigo(int codigo);
