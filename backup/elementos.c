#include "elementos.h"
#include "dragoes.h"
#include <stdlib.h>
#include <string.h>


int ARRSIZEELEMENTO =  5;

Elemento* elemento = NULL;
int i, qtdElemento = 0;



int inicializarElementos()
{
	elemento = (Elemento*) malloc (ARRSIZEELEMENTO * sizeof(Elemento));
    if (elemento == NULL)
	{
		return 0;
	}
	
    for (i = 0; i < ARRSIZEELEMENTO; i++)
    {   	
        elemento[i].codigo = 0;
    }
		elemento[0].codigo = 1;
        strcpy(elemento[0].nome, "fogo"); 
        strcpy(elemento[0].vulnerabilidade, "agua");
		// elemento[1].codigo = 2;
        // strcpy(elemento[1].nome, "agua"); 
        // strcpy(elemento[1].vulnerabilidade, "fogo");
		// elemento[2].codigo = 3;
        // strcpy(elemento[2].nome, "pedra"); 
        // strcpy(elemento[2].vulnerabilidade, "divinity original sin 2");
		// elemento[3].codigo = 4;
        // strcpy(elemento[3].nome, "sol"); 
        // strcpy(elemento[3].vulnerabilidade, "entropia");
		// elemento[4].codigo = 5;
        // strcpy(elemento[4].nome, "metallica"); 
        // strcpy(elemento[4].vulnerabilidade, "megadeth");

        qtdElemento = 1;
        
        return 1;
}

int retornaTamanhoElementos()
{
	return qtdElemento;
}

int encerraElementos()
{
	free(elemento);
}

int salvarElemento(Elemento element)
{
    if (elemento != NULL)
    {
    	if (qtdElemento == ARRSIZEELEMENTO)
    	{
    		Elemento* elementoBKP = elemento;
    		elemento = realloc (elemento, (qtdElemento * 2)  * sizeof(Elemento));
    		if (elemento != NULL)
    		{
    			ARRSIZEELEMENTO = ARRSIZEELEMENTO *  2;
			}
			else {
				elemento = elementoBKP;
				return 0;
			}
		}
        elemento[qtdElemento] = element;
        qtdElemento++;
        return 1;
	}else    
    	return 0;
}

int QuantidadeElementos()
{
    return qtdElemento;
}

Elemento* obterElementoPeloIndice(int indice)
{
    Elemento* element = (Elemento*) malloc (sizeof(Elemento));
	*element = elemento[indice];
	return element;
}

Elemento* obterElementoPeloCodigo(int codigo)
{
    int i;
	Elemento* Element = (Elemento*) malloc (sizeof(Elemento));
	Element->codigo = codigo;
	for(i = 0; i < qtdElemento; i++)
	{
		if (codigo == elemento[i].codigo)
		{
			*Element = elemento[i];
			break;
		}
			
	}
		return Element;
}

int atualizarElemento(char* mudanca, int m,int opcao,int codigo)
{
	int i, b, r;
	Elemento* element = obterElementoPeloCodigo(codigo);
	for(i = 0; i < qtdElemento; i++)
	{
		if (element->codigo == elemento[i].codigo)
		{
			break;
		}
	}
	if (opcao == 1)
	{
		strcpy(elemento[i].nome, mudanca);	
		for (b = 0; b < QuantidadeDragoes(); b++)
		{
			Dragao* dragon = obterDragaoPeloIndice(b);
			if (dragon->codigoElemento == codigo) //atualiza o elemento em dragao.c caso algum esteja usando o que foi alterado
			{
				atualizarDragao(codigo, mudanca, m, 3, dragon->codigo);
				break;
			}
		}
	}
	else if (opcao == 2)
	{
		strcpy(elemento[i].vulnerabilidade, mudanca);
	}
	
	free(element);//falta free após chamar obterElementoPeloCodigo
	
	return 0;
}

Elemento* obterElementoPeloNome (char* nome)
{
	Elemento* Element = (Elemento*) malloc (sizeof(Elemento));
	
	for (i = 0; i < qtdElemento; i++)
    {
    	*Element = elemento[i];
        Elemento* element = obterElementoPeloIndice(i);
        if (strcmpi(nome, element->nome) == 0)
            return Element;

    }
    
    return Element = NULL;//falta return no final da função obterElementoPeloNome
}

int ApagarElementoPeloCodigo(int codigo)
{
    int porcentagemArrays = ARRSIZEELEMENTO * 0.4;

	for(i = 0; i < qtdElemento; i++)
	{
		if (elemento[i].codigo == codigo)
		{
			elemento[i] = elemento[qtdElemento-1];
			elemento[qtdElemento - 1].codigo = 0;
			qtdElemento--;

			if (porcentagemArrays == qtdElemento && ARRSIZEELEMENTO > 5)
			{
				Elemento* ArrayMenor = realloc (elemento, (qtdElemento) * sizeof(Elemento));
				if (ArrayMenor != NULL)
				{
					ARRSIZEELEMENTO = qtdElemento;
					elemento = ArrayMenor;
					return 2;
				}else return 0;
			}
			return 1;
		}
	}
	return 0;
}
