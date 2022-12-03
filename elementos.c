#include "elementos.h"
#include "dragoes.h"
#include <stdlib.h>
#include <string.h>


int ARRSIZEELEMENTO =  5;

Elemento* elemento = NULL;
int qtdElemento = 0, codigoAtualElementos = 0;



int inicializarElementos()
{
	elemento = (Elemento*) malloc (ARRSIZEELEMENTO * sizeof(Elemento));
    if (elemento == NULL)
	{
		return 0;
	}
	
	Elemento leitura;
	fclose(elem);

	elem = fopen("file_elem.bin", "r+b");
	if (elem == NULL)
	{
		exit(1);
	}
	while(fread(&leitura, sizeof(Elemento), 1, elem))
	{
		if(leitura.codigo > codigoAtualElementos)
			codigoAtualElementos = leitura.codigo;
		qtdElemento++;
	}
    return 1;
}

int retornaTamanhoElementos()
{
	return qtdElemento;
}

int encerraElementos()
{
	fclose(elem);
}

int salvarElemento(Elemento element)
{
	element.codigo = ++codigoAtualElementos;

	fseek(elem, 0, SEEK_END);
	fwrite(&element, sizeof(Elemento), 1, elem);

	qtdElemento++;

    return 1;
}

int QuantidadeElementos()
{
    return qtdElemento;
}

Elemento* obterElementoPeloIndice(int indice)
{
    Elemento* element = (Elemento*) malloc (sizeof(Elemento));
	fseek(elem, indice * sizeof(Elemento), SEEK_SET);
	fread(element, sizeof(Elemento), 1, elem);

	return element;;
}

Elemento* obterElementoPeloCodigo(int codigo)
{
    int i;
	Elemento* element = (Elemento*) malloc (sizeof(Elemento));
	for(i = 0; i < qtdElemento; i++)
	{
		fseek(elem, i * sizeof(Elemento), SEEK_SET);
		fread(element, sizeof(Elemento), 1, elem);
		if (element->codigo == codigo)
		{
			fwrite(element, sizeof(Elemento), 1, elem);
			return element;
		}
	}
	return NULL;
}

int atualizarElemento(char* mudanca, int m,int opcao,int codigo)
{
	int i;
	Elemento* element = (Elemento*) malloc (sizeof(Elemento));
	for(i = 0; i < qtdElemento; i++)
	{
		fseek(elem, i * sizeof(Elemento), SEEK_SET);
		fread(element, sizeof(Elemento), 1, elem);
		if (element->codigo == codigo)
		{
			break;
		}
	}
	if (opcao == 1)
	{
		strcpy(element->nome, mudanca);
		fseek(elem, i * sizeof(Elemento), SEEK_SET);
		fwrite(element, sizeof(Elemento), 1, elem);
	}
	else if (opcao == 2)
	{
		strcpy(element->vulnerabilidade, mudanca);
		fseek(elem, i * sizeof(Elemento), SEEK_SET);
		fwrite(element, sizeof(Elemento), 1, elem);
	}
	free(element);
	
	return 0;
}

Elemento* obterElementoPeloNome (char* nome)
{
	int i;
	Elemento* element = (Elemento*) malloc (sizeof(Elemento));
	for(i = 0; i < qtdElemento; i++)
	{
		fseek(elem, i * sizeof(Elemento),  SEEK_SET);
		fread(element, sizeof(Elemento), 1, elem);
		if (strcmpi(nome, element->nome) == 0)
		{
			return element;
		}
	}
    return	NULL;
}

int ApagarElementoPeloCodigo(int codigo)
{

	int i;
	for(i = 0; i < QuantidadeDragoes(); i++)
	{
		Dragao* dragon = obterDragaoPeloIndice(i);
		if(dragon->codigoElemento == codigo)
		{
			free(dragon);
			return 3;
		}
	}
	
	FILE* elem_tmp;
	int encontrado = 0;

	elem_tmp = fopen("file_elem_tmp.bin", "wb");
	if (elem_tmp == NULL)
	{
		exit(1);
	}
	Elemento element;
	for(i = 0; i < qtdElemento; i++)
	{
		fseek(elem, i * sizeof(Elemento),  SEEK_SET);
		fread(&element, sizeof(Elemento), 1, elem);
		if (element.codigo == codigo)
		{
			encontrado = 1;
		}else {
			fwrite(&element, sizeof(Elemento), 1, elem_tmp);
		}
	}
	if (encontrado == 0)
	{
		return 2;
	}
	fclose(elem_tmp);
	fclose(elem);
	remove("file_elem.bin");
	rename("file_elem_tmp.bin", "file_elem.bin");
	elem = fopen("file_elem.bin", "r+b");
   	if (elem == NULL)
	{
		exit(1);
	}
	qtdElemento --;
    return 1;
}
