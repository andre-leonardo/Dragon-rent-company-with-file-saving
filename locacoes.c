#include "locacoes.h"
#include "guerreiros.h"
#include "dragoes.h"
#include <stdlib.h>
#include <string.h>



int ARRSIZELOCACAO =  5;

Locacao* locacao = NULL;
int qtdLocacao = 0, codigoAtualLocacoes = 0;


int inicializarLocacoes()
{
	locacao = (Locacao*) malloc (ARRSIZELOCACAO * sizeof(Locacao));
    if (locacao == NULL)
	{
		return 0;
	}
	Locacao leitura;
	fclose(loca);

	loca = fopen("file_loca.bin", "r+b");
	if (loca == NULL)
	{
		exit(1);
	}
	while(fread(&leitura, sizeof(Locacao), 1, loca))
	{
		if(leitura.codigoLocacao > codigoAtualLocacoes)
			codigoAtualLocacoes = leitura.codigoLocacao;
		qtdLocacao++;
	}
    return 1;

}

int retornaTamanhoLocacoes()
{
	return ARRSIZELOCACAO;
}

int encerraLocacoes()
{
    fclose(loca);
}

int salvarLocacao(Locacao location, int codDrag, int codGuerr, int qtd)
{
    int i; 

    

        for (i = 0; i < QuantidadeGuerreiros(); i++)
        {
            Guerreiro* warrior = obterGuerreiroPeloIndice(i);
            if (codGuerr == warrior->codigo)
            {
                registrarLocacaoGuerr(codGuerr, 1);
                location.codigoGuerreiroLocador = codGuerr;
                free(warrior);
                break;
            }
        }

        for (i = 0; i < QuantidadeDragoes(); i++)
        {
            Dragao* dragon = obterDragaoPeloIndice(i);
            if (codDrag == dragon->codigo)
            {
                if(qtd > dragon->unidade || qtd < 0)
                {
                    return 2;
                }
                
                dragon->unidade = dragon->unidade - qtd;
                registrarMudancaDrag(dragon->unidade, dragon->codigo);
                registrarLocacaoDrag(dragon->codigo, 1);

                location.codigoLocacao = ++codigoAtualLocacoes;
                location.valorDiario = dragon->valor * qtd;
                location.quantidadeLocada = qtd;
                location.codigoDragaoLocado = dragon->codigo;
                //<data
                struct tm *tempo;
                time_t segundos;
                time(&segundos); 
                tempo = localtime(&segundos);

                strcpy(location.dataInicio, asctime(tempo)); 
                //data>

                qtdLocacao++;
                location.locacaoNaoDevolvida = 1;
                fseek(loca, 0, SEEK_END);
                fwrite(&location, sizeof(Locacao), 1, loca);
                free(dragon);
                return 1;
                
            }
        }
	
}

int QuantidadeLocacoes()
{
    return qtdLocacao;
}



Locacao* obterLocacaoPeloIndice(int indice)
{
    Locacao* location = (Locacao*) malloc (sizeof(Locacao));
	fseek(loca, indice * sizeof(Locacao), SEEK_SET);
	fread(location, sizeof(Locacao), 1, loca);
	return location;
}

Locacao* obterLocacaoPeloCodigo(int codigo)
{
    int i;
	Locacao* location = (Locacao*) malloc (sizeof(Locacao));
	for(i = 0; i < qtdLocacao; i++)
	{
        fseek(loca, i * sizeof(Locacao), SEEK_SET);
        fread(location, sizeof(Locacao), 1, loca);
		if (location->codigoLocacao == codigo)
		{
			fwrite(location, sizeof(Locacao), 1, loca);
			return location;
		}		
	}
	return NULL;
}




int DevolverLocacaoPeloCodigo(int codigo)
{
    int i;
    Locacao* location = obterLocacaoPeloCodigo(codigo);
    if(location->locacaoNaoDevolvida > 0)
    {
    Guerreiro* warrior = obterGuerreiroPeloCodigo(location->codigoGuerreiroLocador);

    Dragao* dragon = obterDragaoPeloCodigo(location->codigoDragaoLocado);
    dragon->unidade = dragon->unidade + location->quantidadeLocada;
    registrarMudancaDrag(dragon->unidade, dragon->codigo);

    registrarLocacaoGuerr(warrior->codigo, 2);
    registrarLocacaoDrag(dragon->codigo, 2);

    for (i = 0; i < qtdLocacao; i++)
	{
		fseek(loca, i * sizeof(Dragao), SEEK_SET);
		fread(location, sizeof(Dragao), 1, loca);
		if (location->codigoLocacao == codigo)
		{
			break;
		}
	}
    //<data   
    struct tm *tempo;
    time_t segundos;
    time(&segundos); 
    tempo = localtime(&segundos);
    location->locacaoNaoDevolvida = 0;
    strcpy(location->dataFim, asctime(tempo)); 
    fseek(loca, i * sizeof(Locacao), SEEK_SET);
	fwrite(location, sizeof(Locacao), 1, loca);
        

    //data>
    
    free(location);
    free(warrior);
    free(dragon);
    
    
    return 1;
    }
    return 2;
            
}

int ExcluirLocacao(int codigo)
{
    int i;
    int porcentagemArrays = ARRSIZELOCACAO * 0.4;
    for (i = 0; i < qtdLocacao; i++)
    {
        
        if (locacao[i].codigoLocacao == codigo)
        {
            if (locacao[i].locacaoNaoDevolvida == 1)
            {
                return 0;
            }else{
                locacao[i].codigoLocacao == 0;
                qtdLocacao--;
                if (porcentagemArrays == qtdLocacao && ARRSIZELOCACAO > 5)
                {
                    Dragao* ArrayMenor = realloc (locacao, (qtdLocacao) * sizeof(Locacao));
                    if (ArrayMenor != NULL)
                    {
                        ARRSIZELOCACAO = qtdLocacao;
                        locacao = ArrayMenor;
                        return 2;
                    }else return 0;
                }
                return 1;
            }
        }
    }
}






// Locacao* obterLocacaoPeloCodigoDragao(int codigo)
// {
//     int i;
// 	Locacao* Location = (Locacao*) malloc (sizeof(Locacao));
// 	for(i = 0; i < qtdLocacao; i++)
// 	{
// 		if (locacao[i].codigoDragaoLocado == codigo)
// 		{
// 			*Location = locacao[i];
// 			return Location;
// 		}		
// 	}
// 	return NULL;
// }

// Locacao* obterLocacaoPeloCodigoGuerreiro(int codigo)
// {
//     int i;
// 	Locacao* Location = (Locacao*) malloc (sizeof(Locacao));
// 	for(i = 0; i < qtdLocacao; i++)
// 	{
// 		if (locacao[i].codigoGuerreiroLocador == codigo)
// 		{
// 			*Location = locacao[i];
// 			return Location;
// 		}		
// 	}
// 	return NULL;
// }