#include "guerreiros.h"
#include "locacoes.h"
#include <stdlib.h>
#include <string.h>

int qtdGuerreiro = 0;
int codigoAtualGuerreiros = 0;


int inicializarGuerreiros()
{
    Guerreiro leitura;
    fclose(guerr);
    
   	guerr = fopen("file_guerr.bin", "r+b");
   	if (guerr == NULL)
	{
		exit(1);
	}
    while(fread(&leitura, sizeof(Guerreiro), 1, guerr))//contar o que ja esta escrito
    {
		if(leitura.codigo > codigoAtualGuerreiros)
			codigoAtualGuerreiros = leitura.codigo;
    	qtdGuerreiro++;
	}
    return 1;
}


int encerraGuerreiros()
{
	fclose(guerr);
}

int salvarGuerreiro(Guerreiro warrior)
{
	warrior.codigo = ++codigoAtualGuerreiros;
	
    fseek(guerr, 0,  SEEK_END);
	fwrite(&warrior, sizeof(Guerreiro), 1, guerr);
	
	qtdGuerreiro++;
	
	return 1;
}


int QuantidadeGuerreiros()
{
    return qtdGuerreiro;
}

Guerreiro* obterGuerreiroPeloIndice(int indice)
{
	Guerreiro* warrior = (Guerreiro*) malloc (sizeof(Guerreiro));
	fseek(guerr, indice * sizeof(Guerreiro),  SEEK_SET);
	fread(warrior, sizeof(Guerreiro), 1, guerr);
	
	return warrior;
}

Guerreiro* obterGuerreiroPeloCodigo(int codigo)
{
	int i;
	Guerreiro* warrior = (Guerreiro*) malloc (sizeof(Guerreiro));
	for (i = 0; i < qtdGuerreiro; i++)
	{
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fread(warrior, sizeof(Guerreiro), 1, guerr);
		if (warrior->codigo == codigo)
		{
			fwrite(warrior, sizeof(Guerreiro), 1, guerr);
			return warrior;
		}		
	}
	return NULL;
}

int atualizarGuerreiro(char* mudanca, int m, int opcao,int codigo)
{
	int i;
	Guerreiro* warrior = obterGuerreiroPeloCodigo(codigo);
	for(i = 0; i < qtdGuerreiro; i++)
	{
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fread(warrior, sizeof(Guerreiro), 1, guerr);
		if (warrior->codigo == codigo)
		{
			break;//salvar o valor de i
		}
	}
	if (opcao == 1)
	{
		strcpy(warrior->nome, mudanca);
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fwrite(warrior, sizeof(Guerreiro), 1, guerr);
	}
	else if (opcao == 2)
	{
		strcpy(warrior->titulo, mudanca);
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fwrite(warrior, sizeof(Guerreiro), 1, guerr);
	}
	else if (opcao == 3)
	{
		strcpy(warrior->reino, mudanca);	
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fwrite(warrior, sizeof(Guerreiro), 1, guerr);
	}
		
	free (warrior);//chamar free em DevolverLocacaoPeloCodigo e em atualizarGuerreiro
}


Guerreiro* obterGuerreiroPeloNome (char* nome)
{
	int i;
	Guerreiro* warrior = (Guerreiro*) malloc (sizeof(Guerreiro));
	for(i = 0; i < qtdGuerreiro; i++)
	{
		fseek(guerr, i * sizeof(Guerreiro),  SEEK_SET);
		fread(warrior, sizeof(Guerreiro), 1, guerr);
		if (strcmpi(nome, warrior->nome) == 0)
		{
			return warrior;
		}
	}
    return	NULL;
}

int ApagarGuerreiroPeloCodigo(int codigo)
{
	int i;
	FILE* guerr_tmp;
	int encontrado = 0;

	guerr_tmp = fopen("file_guerr_tmp.bin", "wb");
	if (guerr_tmp == NULL)
	{
		exit(1);
	}
	Guerreiro warrior;
	for(i = 0; i < qtdGuerreiro; i++)
	{
		fseek(guerr, i * sizeof(Guerreiro),  SEEK_SET);
		fread(&warrior, sizeof(Guerreiro), 1, guerr);
		if (warrior.codigo == codigo)
		{
			encontrado = 1;
		}else {
			fwrite(&warrior, sizeof(Guerreiro), 1, guerr_tmp);
		}
	}
	if (encontrado == 0)
	{
		return 2;
	}
	fclose(guerr_tmp);
	fclose(guerr);
	remove("file_guerr.bin");
	rename("file_guerr_tmp.bin", "file_guerr.bin");
	guerr = fopen("file_guerr.bin", "r+b");
   	if (guerr == NULL)
	{
		exit(1);
	}
	qtdGuerreiro --;
    return 1;
}

int registrarLocacaoGuerr(int cod, int aumentarOuDiminuir)
{
	int i;

	Guerreiro* warrior = obterGuerreiroPeloCodigo(cod);

	for(i = 0; i < qtdGuerreiro; i++)
	{
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fread(warrior, sizeof(Guerreiro), 1, guerr);
		if (warrior->codigo == cod)
		{
			break;
		}
	}
	if (aumentarOuDiminuir == 1)
	{
		warrior->checarLocacao = ++warrior->checarLocacao;
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fwrite(warrior, sizeof(Guerreiro), 1, guerr);
	}
	else
	{
		warrior->checarLocacao = --warrior->checarLocacao;
		fseek(guerr, i * sizeof(Guerreiro), SEEK_SET);
		fwrite(warrior, sizeof(Guerreiro), 1, guerr);	
	}
}




