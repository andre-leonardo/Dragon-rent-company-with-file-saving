#include "dragoes.h"
#include "elementos.h"
#include "locacoes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ARRSIZEDRAGAO =  5;


Dragao* dragao = NULL;
int qtdDragao = 0, codigoAtualDragoes = 0;


int inicializarDragoes()
{
	int i;
    dragao = (Dragao*) malloc (ARRSIZEDRAGAO * sizeof(Dragao));
    if (dragao == NULL)
	{
		return 0;
	}

	Dragao leitura;
	drag = fopen("drag.bin", "r+b");
	if (drag == NULL)
	{
		exit(1);
	}
	while(fread(&leitura, sizeof(Dragao), 1, drag))
	{
		if(leitura.codigo > codigoAtualDragoes)
			codigoAtualDragoes = leitura.codigo;
		qtdDragao++;
	}
    return 1;
}


int encerraDragoes()
{
	fclose(drag);
}



int salvarDragao(Dragao dragon)
{ 
	dragon.codigo = ++codigoAtualDragoes;

	fseek(drag, 0, SEEK_END);
	fwrite(&dragon, sizeof(Dragao), 1, drag);

	qtdDragao++;

    return 1;
}

int QuantidadeDragoes()
{
    return qtdDragao;
}


Dragao* obterDragaoPeloIndice(int indice)
{
    Dragao* dragon = (Dragao*) malloc (sizeof(Dragao));
	fseek(drag, indice * sizeof(Dragao), SEEK_SET);
	fread(dragon, sizeof(Dragao), 1, drag);

	return dragon;
}

Dragao* obterDragaoPeloCodigo(int codigo)
{
	int i;
	Dragao* dragon = (Dragao*) malloc (sizeof(Dragao));
	for(i = 0; i < qtdDragao; i++)
	{
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fread(dragon, sizeof(Dragao), 1, drag);
		if (dragon->codigo == codigo)
		{
			fwrite(dragon, sizeof(Dragao), 1, drag);
			return dragon;
		}
	}
	return NULL;
}

int atualizarDragao(int mudancaInt, char* mudanca, int m, int opcao,int codigo)
{
	int i;
	Dragao* dragon = obterDragaoPeloCodigo(codigo);
	for(i = 0; i < qtdDragao; i++)
	{
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fread(dragon, sizeof(Dragao), 1, drag);
		if (dragon->codigo == codigo)
		{
			break;
		}
	}
	if (opcao == 1)
	{
		strcpy(dragon->nome, mudanca);
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fwrite(dragon, sizeof(Dragao), 1, drag);
	}	
	else if (opcao == 2)
	{
		dragon->idade = mudancaInt;
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fwrite(dragon, sizeof(Dragao), 1, drag);
	}
	else if (opcao == 3)
	{
		Elemento* element = obterElementoPeloCodigo(mudancaInt);
		dragon->codigoElemento = element->codigo;
		free(element);//falta free ap�s chamar obterElementoPeloCodigo
	}
	else if (opcao == 4)
		dragon->valor = mudancaInt;
	else if (opcao == 5)
		dragon->unidade = mudancaInt;
		
	free(dragon);//na fun��o DevolverLocacaoPeloCodigo, precisa de free. a mesma coisa em registrarMudancaDrag e em atualizarDragao
	return 0;
}

Dragao* obterDragaoPeloNome (char* nome)
{
	int i;
	Dragao* Dragon = (Dragao*) malloc (sizeof(Dragao));
	
	for (i = 0; i < qtdDragao; i++)
    {
    	*Dragon = dragao[i];
        if (strcmpi(nome, dragao[i].nome) == 0)
            return Dragon;
    }
    
    return Dragon = NULL;//falta return no final da fun��o obterDragaoPeloNome
}

int ApagarDragaoPeloCodigo(int codigo)
{
	int i;
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

