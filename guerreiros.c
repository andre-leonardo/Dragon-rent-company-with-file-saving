#include "guerreiros.h"
#include "locacoes.h"
#include <stdlib.h>
#include <string.h>
int ARRSIZEGUERREIRO = 5;



Guerreiro *guerreiro = NULL;
int i, qtdGuerreiro = 0;


int inicializarGuerreiros()
{
	
	guerreiro = (Guerreiro*) malloc (ARRSIZEGUERREIRO * sizeof(Guerreiro));
	if (guerreiro == NULL)
	{
		return 0;
	}
	
    Guerreiro leitura;
    
   	guerr = fopen("guerr.bin", "rb");
    while(fread(&leitura, sizeof(Guerreiro), 1, guerr))//contar o que ja esta escrito
    	qtdGuerreiro++;
    	
    fclose(guerr);
    
    return 1;
}


int encerraGuerreiros()
{
	free(guerreiro);
	guerreiro = NULL;
}

int salvarGuerreiro(Guerreiro warrior)
{
	guerr = fopen("guerr.bin", "ab");
	if (guerr == NULL)
	{
		exit(1);
	}

	fwrite(&warrior, sizeof(Guerreiro), 1, guerr);
	fclose(guerr);
	qtdGuerreiro++;
}

int registrarLocacaoGuerr(int cod, int aumentarOuDiminuir)
{
	int i;

	if (aumentarOuDiminuir == 1)
	{
		for (i = 0; i < qtdGuerreiro; i++)
		{
			if (guerreiro[i].codigo == cod)
			{
				guerreiro[i].checarLocacao = guerreiro[i].checarLocacao + 1;
				break;
			}
		}	
	}
	else
	{
		for (i = 0; i < qtdGuerreiro; i++)
		{
			if (guerreiro[i].codigo == cod)
			{
				guerreiro[i].checarLocacao = guerreiro[i].checarLocacao - 1;
				break;
			}
		}	
	}
}

int QuantidadeGuerreiros()
{
    return qtdGuerreiro;
}

Guerreiro* obterGuerreiroPeloIndice(int indice)
{
	Guerreiro* warrior = (Guerreiro*) malloc (sizeof(Guerreiro));
	*warrior = guerreiro[indice];
	return warrior;
}

Guerreiro* obterGuerreiroPeloCodigo(int codigo)
{
	int i;
	Guerreiro* Warrior = (Guerreiro*) malloc (sizeof(Guerreiro));
	Warrior->codigo = codigo;
	for(i = 0; i < qtdGuerreiro; i++)
	{
		if (guerreiro[i].codigo == codigo)
		{
			*Warrior = guerreiro[i];
			return Warrior;
		}		
	}
	
	return NULL;//quando chega no final da fun��o (ap�s o FOR) precisa de return
}

int atualizarGuerreiro(char* mudanca, int m, int opcao,int codigo)
{
	int i, b;
	Guerreiro* warrior = obterGuerreiroPeloCodigo(codigo);
	for(i = 0; i < qtdGuerreiro; i++)
	{
		if (warrior->codigo == guerreiro[i].codigo)
		{
			break;
		}
	}
	if (opcao == 1)
	{
		strcpy(guerreiro[i].nome, mudanca);
		for (b = 0; b < QuantidadeLocacoes(); b++)
		{
			Locacao* locacao = obterLocacaoPeloIndice(b);
			if (locacao->codigoGuerreiroLocador == codigo)
			{
				atualizarLocacao(mudanca, 30, 2, codigo);
				free (locacao);
				break;
			}
		}
	}
	else if (opcao == 2)
		strcpy(guerreiro[i].titulo, mudanca);
	else if (opcao == 3)
		strcpy(guerreiro[i].reino, mudanca);	
		
	free (warrior);//chamar free em DevolverLocacaoPeloCodigo e em atualizarGuerreiro
}

Guerreiro obterGuerreiroPeloNome (char* nome)
{
	guerr = fopen("guerr.bin", "rb");
	if (guerr == NULL)
	{
		exit(1);
	}
	Guerreiro warrior;
	while(fread(&warrior, sizeof(Guerreiro), 1, guerr))
	{
        if (strcmpi(nome, warrior.nome) == 0)
        {
            return warrior;
        }
    }

	fclose(guerr);

    return	warrior;//quando chega no final da fun��o (ap�s o FOR) precisa de return
}

int ApagarGuerreiroPeloCodigo(int codigo)
{

	FILE* guerr_tmp;
	int encontrado = 0;
	guerr = fopen("guerr.bin", "rb");
	if (guerr == NULL)
	{
		exit(1);
	}

	guerr_tmp = fopen("guerr_tmp.bin", "wb");
	if (guerr_tmp == NULL)
	{
		exit(1);
	}
	Guerreiro warrior;
	while(fread(&warrior, sizeof(Guerreiro), 1, guerr))
	{
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
	fclose(guerr);
	fclose(guerr_tmp);
	remove("guerr.bin");
	rename("guerr_tmp.bin", "guerr.bin");
    return 1;
}




