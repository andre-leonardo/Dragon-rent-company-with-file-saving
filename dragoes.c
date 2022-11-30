#include "dragoes.h"
#include "elementos.h"
#include "locacoes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ARRSIZEDRAGAO =  5;


Dragao* dragao = NULL;
int i, qtdDragao = 0;


int inicializarDragoes()
{
    dragao = (Dragao*) malloc (ARRSIZEDRAGAO * sizeof(Dragao));
    if (dragao == NULL)
	{
		return 0;
	}

    for (i = 0; i < ARRSIZEDRAGAO; i++)
    {   	
        dragao[i].codigo = 0;
        // dragao[i].nome[0] = '\0';
        dragao[i].idade = 0;
        dragao[i].valor = 0;
        dragao[i].unidade = 0;
        // dragao[i].elemento[0] = '\0';
        dragao[i].checarLocacao = 0;
        // dragao[i].unidadeAnterior[i] = 0;
    }
        return 1;
}


int encerraDragoes()
{
	free(dragao);
}



int salvarDragao(Dragao dragon)
{ 
        
	drag = fopen("drago.bin", "ab");
	if (drag == NULL)
	{
		exit(1);
	}

	fwrite(&dragon, sizeof(Dragao), 1, drag);
	fclose(drag);
}

int QuantidadeDragoes()
{
    return qtdDragao;
}
int registrarMudancaDrag(int qtd, int cod)//alterar o valor de unidade
{
	int i;
	Dragao* dragon = obterDragaoPeloCodigo(cod);
	for (i = 0; i < qtdDragao; i++)
		{

			if (dragao[i].codigo == dragon->codigo)
			{
				dragao[i].unidade = qtd;
				return 0;
			}
		}
	return 1;
}

int registrarLocacaoDrag(int cod, int aumentarOuDiminuir)
{
	int i;

	if (aumentarOuDiminuir == 1)
	{
		for (i = 0; i < qtdDragao; i++)
		{
			if (dragao[i].codigo == cod)
			{
				dragao[i].checarLocacao = dragao[i].checarLocacao + 1;
				return 1;
			}
		}	
	}
	if (aumentarOuDiminuir == 2)
	{
		for (i = 0; i < qtdDragao; i++)
		{
			if (dragao[i].codigo == cod)
			{
				dragao[i].checarLocacao = dragao[i].checarLocacao - 1;
				return 2;
			}
		}	
	}
}

Dragao* obterDragaoPeloIndice(int indice)
{
    Dragao* dragon = (Dragao*) malloc (sizeof(Dragao));
	*dragon = dragao[indice];
	return dragon;
}

Dragao* obterDragaoPeloCodigo(int codigo)
{
	int i;
	Dragao* Dragon = (Dragao*) malloc (sizeof(Dragao));
	for(i = 0; i < qtdDragao; i++)
	{
		if (dragao[i].codigo == codigo)
		{
			*Dragon = dragao[i];
			return Dragon;
		}		
	}
}

int atualizarDragao(int mudancaInt, char* mudanca, int m, int opcao,int codigo)
{
	int i, b;
	Dragao* dragon = obterDragaoPeloCodigo(codigo);
	for(i = 0; i < qtdDragao; i++)
	{
		if (dragon->codigo == dragao[i].codigo)
		{
			break;
		}
	}
	if (opcao == 1)
	{
		strcpy(dragao[i].nome, mudanca);
		for (b = 0; b < QuantidadeLocacoes(); b++)
		{
			Locacao* locacao = obterLocacaoPeloIndice(b);
			if (locacao->codigoDragaoLocado == codigo)
			{
				atualizarLocacao(mudanca, 30, 1, codigo);
				free(locacao);
				break;
			}
		}
	}	
	else if (opcao == 2)
		dragao[i].idade = mudancaInt;
	else if (opcao == 3)
	{
		Elemento* element = obterElementoPeloCodigo(mudancaInt);
		dragao[i].codigoElemento = element->codigo;
		strcpy(dragao[i].elemento, element->nome);
		free(element);//falta free ap�s chamar obterElementoPeloCodigo
	}
	else if (opcao == 4)
		dragao[i].valor = mudancaInt;
	else if (opcao == 5)
		dragao[i].unidade = mudancaInt;
		
	free(dragon);//na fun��o DevolverLocacaoPeloCodigo, precisa de free. a mesma coisa em registrarMudancaDrag e em atualizarDragao
	return 0;
}

Dragao* obterDragaoPeloNome (char* nome)
{
	Dragao* Dragon = (Dragao*) malloc (sizeof(Dragao));
	
	for (i = 0; i < qtdDragao; i++)
    {
    	*Dragon = dragao[i];
        if (strcmpi(nome, dragao[i].nome) == 0)
            return Dragon;
    }
    
    return Dragon = NULL;//ta return no final da fun��o obterDragaoPeloNome
}

int ApagarDragaoPeloCodigo(int codigo)
{
	int porcentagemArrays = ARRSIZEDRAGAO * 0.4;

    for(i = 0; i < qtdDragao; i++)
    {
        if (dragao[i].codigo == codigo)
        {
			if (dragao[i].checarLocacao > 0)
				return 3;
            dragao[i] = dragao[qtdDragao-1];
            dragao[qtdDragao - 1].codigo = 0;
            qtdDragao--;
			if (porcentagemArrays == qtdDragao && ARRSIZEDRAGAO > 5)
			{
				Dragao* ArrayMenor = realloc (dragao, (qtdDragao) * sizeof(Dragao));
				if (ArrayMenor != NULL)
				{
					ARRSIZEDRAGAO = qtdDragao;
					dragao = ArrayMenor;
					return 2;
				}else return 0;
			}
            return 1;
        }
    }
    return 0;
}


//  ⣿⣿⣿⣿⣿⡏⠉⠄⠄⠄⠄⠄⠄⠄⠄⠈⠉⠉⠉⠉⠉⠉⠉⢿⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠸⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⠄⠄⣀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⠄⢠⡏⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿ 
//  ⣍⡉⠙⠛⠛⠄⠾⢀⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠙⠛⠛⠛⠛⣛ 
//  ⣿⣿⣶⣦⣄⢀⣀⡀⠄⠉⠉⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⡀⠄⣤⣤⣶⣶⣾⣿ 
//  ⣿⣿⣿⣿⠛⠸⣿⣿⣿⣿⣟⣿⣿⣿⣿⣿⣟⣻⣾⣿⣿⣿⡅⠄⢻⢿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣧⡃⠄⢀⠤⠄⠄⠄⠄⠄⢀⡀⠄⢠⡤⠄⠄⠄⠄⠄⠄⡇⢠⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⡇⠄⢹⠄⠄⠄⠄⠄⠄⢸⣿⠄⠘⠄⠄⠄⠄⠄⠄⢸⢀⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⡝⡇⢄⣀⣀⣀⣀⣠⣴⣸⣿⠄⠈⢀⠄⢀⣀⡀⠄⢨⣾⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⣅⠸⣿⣿⣿⣿⣹⡿⠿⡿⠇⠋⡻⣿⣿⠟⠄⠄⣦⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⣿⠄⣿⡽⣿⠗⠋⠉⠁⠈⠄⠉⠘⠛⣿⢠⠄⠄⣿⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⣿⣧⡘⣿⠏⠄⣠⣤⣄⣠⣤⣀⣠⣄⠻⢸⠃⣼⣿⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⣿⣿⣷⣸⠄⢐⢿⡏⠁⠄⠈⢹⠿⠟⢀⣾⣾⣿⣿⣿⣿⣿⣿⣿⣿ 
//  ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠃⠈⠁⠄⠄⠄⠈⠄⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ 

