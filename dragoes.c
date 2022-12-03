#include "dragoes.h"
#include "elementos.h"
#include "locacoes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ARRSIZEDRAGAO =  5;


Dragao* dragao = NULL;
int qtdDragao = 0;
int codigoAtualDragoes = 0;


int inicializarDragoes()
{
    dragao = (Dragao*) malloc (ARRSIZEDRAGAO * sizeof(Dragao));
    if (dragao == NULL)
	{
		return 0;
	}

	Dragao leitura;
	fclose(drag);

	drag = fopen("file_drag.bin", "r+b");
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
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fwrite(dragon, sizeof(Dragao), 1, drag);
		free(element);//falta free ap�s chamar obterElementoPeloCodigo
	}
	else if (opcao == 4)
	{
		dragon->valor = mudancaInt;
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fwrite(dragon, sizeof(Dragao), 1, drag);
	}
	else if (opcao == 5)
	{
		dragon->unidade = mudancaInt;
		fseek(drag, i * sizeof(Dragao), SEEK_SET);
		fwrite(dragon, sizeof(Dragao), 1, drag);
	}
		
	free(dragon);
	return 0;
}

Dragao* obterDragaoPeloNome (char* nome)
{
	int i;
	Dragao* dragon = (Dragao*) malloc (sizeof(Dragao));
	for(i = 0; i < qtdDragao; i++)
	{
		fseek(drag, i * sizeof(Dragao),  SEEK_SET);
		fread(dragon, sizeof(Dragao), 1, drag);
		if (strcmpi(nome, dragon->nome) == 0)
		{
			return dragon;
		}
	}
    return	NULL;
}

int ApagarDragaoPeloCodigo(int codigo)
{
	int i;
	FILE* drag_tmp;
	int encontrado = 0;

	drag_tmp = fopen("file_drag_tmp.bin", "wb");
	if (drag_tmp == NULL)
	{
		exit(1);
	}
	Dragao dragon;
	for(i = 0; i < qtdDragao; i++)
	{
		fseek(drag, i * sizeof(Dragao),  SEEK_SET);
		fread(&dragon, sizeof(Dragao), 1, drag);
		if (dragon.codigo == codigo)
		{
			encontrado = 1;
		}else {
			fwrite(&dragon, sizeof(Dragao), 1, drag_tmp);
		}
	}
	if (encontrado == 0)
	{
		return 2;
	}
	fclose(drag_tmp);
	fclose(drag);
	remove("file_drag.bin");
	rename("file_drag_tmp.bin", "file_drag.bin");
	drag = fopen("file_drag.bin", "r+b");
   	if (drag == NULL)
	{
		exit(1);
	}
	qtdDragao --;
    return 1;
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

