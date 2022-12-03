#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dragoes.h"
#include "guerreiros.h"
#include "elementos.h"
#include "locacoes.h"




//GUERREIROS

void listarGuerreiros()
{
	int i;
	if (QuantidadeGuerreiros() == 0)
    {
        printf("NENHUM GUERREIRO CADASTRADO\n");
    }else{
		for (i = 0; i < QuantidadeGuerreiros(); i++)
		{
			Guerreiro* warrior = obterGuerreiroPeloIndice(i);
			printf("\n%d - %s, titulo: %s, reino: %s, quantidade de locacoes no momento: %d\n\n",
				warrior->codigo, warrior->nome,
				warrior->titulo, warrior->reino, warrior->checarLocacao);
			free(warrior);
		}
	}
}

void funcaoCadastroGuerreiro()
{
    Guerreiro warrior;

	

	fflush(stdin);
	printf("Digite o nome do guerreiro: ");
    scanf("%[^\n]s", warrior.nome);
    fflush(stdin);

    printf("Digite o reino do guerreiro: ");
    scanf("%[^\n]s", warrior.reino);
    fflush(stdin);

    printf("Digite o titulo do guerreiro: ");
    scanf("%[^\n]s", warrior.titulo);
    fflush(stdin);

    if (salvarGuerreiro(warrior) == 1)
        printf("Guerreiro cadastrado com sucesso!\n");
    else
        printf("Falha ao cadastrar guerreiros!\n");
}

void funcaoPesquisarGuerreiro()
{
    char procurado[30];
    int i;

    fflush(stdin);
    printf("Digite o nome do guerreiro: ");
	scanf("%[^\n]s", procurado);
	Guerreiro* warrior = obterGuerreiroPeloNome(procurado);

	printf("O codigo do guerreiro eh: %d\n", warrior->codigo);
	printf("Seu titulo eh: %s\n", warrior->titulo);
    printf("Seu reino eh: %s\n", warrior->reino);
	
	free(warrior);
}

void funcaoExcluirGuerreiro()
{
    listarGuerreiros();
    int codigo;
    printf("Digite o codigo do guerreiro que deseja APAGAR: ");
	scanf("%d", &codigo);
	int r = ApagarGuerreiroPeloCodigo(codigo);
	if (r==1)
		printf("Guerreiro APAGADO com sucesso!\n");
	else if (r==2)
		printf("Nenhum guerreiro com este codigo foi encontrado.\n");
	else if (r==3)
		printf("Para ser apagado do sistema o guerreiro deve devolver todos os seus dragoes antes!\n");
	else
		printf("Falha ao apagar o guerreiro!\n");
}

void alterarGuerreiros()
{
	int i, opcao, r;
	char mudanca[30];
	listarGuerreiros();
	int codigo;
	printf("Digite o codigo do guerreiro que deseja alterar: ");
	scanf("%d", &codigo);

	do
	{
	printf("\n0 - Finalizar\n1 - Alterar nome\n2 - Alterar titulo\n3 - Alterar reino\n");
	printf("Digite a numero do que deseja alterar: ");
	scanf("%d", &opcao);
	
	if (opcao == 0)
	{
		printf("Finalizado!\n");
		break;
	}
	else if (opcao == 1)
	{
		printf("Digite o novo nome: ");
		fflush(stdin);
		scanf("%[^\n]s", mudanca);
		r = atualizarGuerreiro(mudanca, 30, 1, codigo);
	}
	else if (opcao == 2)
	{
		printf("Digite o novo titulo: ");
		fflush(stdin);
		scanf("%[^\n]s", mudanca);
		r = atualizarGuerreiro(mudanca, 30, 2, codigo);
	}
	else if (opcao == 3)
	{
		printf("Digite o novo reino: ");
		fflush(stdin);
		scanf("%[^\n]s", mudanca);
		r = atualizarGuerreiro(mudanca, 30, 3, codigo);
	}
	else printf("Numero invalido!n");
	
			
	} while (opcao != 0);
		
}


//DRAGOES
void listarElementos()
{
	int i;

    
    for (i = 0; i < QuantidadeElementos(); i++)
    {
        Elemento* element = obterElementoPeloIndice(i);
        if (element->codigo > 0)		
            printf("\n%d - %s, vulnerabilidade: %s\n\n",
            element->codigo, element->nome, element->vulnerabilidade);
            free(element);//falta free em v�rias fun��es depois de chamar obterElementoPeloIndice
    }
    if (QuantidadeElementos() == 0)
    {
        printf("NENHUM ELEMENTO CADASTRADO\n");
    }
}

void listarDragoes()
{
	int i;
	if (QuantidadeDragoes() == 0)
    {
        printf("NENHUM DRAGAO CADASTRADO\n");
    }else{
		for (i = 0; i < QuantidadeDragoes(); i++)
		{
			Dragao* dragon = obterDragaoPeloIndice(i);
			Elemento* element = obterElementoPeloCodigo(dragon->codigoElemento);
			printf("\n%d - %s, idade: %d, elemento: %s, valor: %.2f, quantidade: %d, esta sendo locado por %d pessoas\n\n",
				dragon->codigo, dragon->nome, dragon->idade, element->nome, 
				dragon->valor, dragon->unidade, dragon->checarLocacao);
			free(dragon);
			free(element);
		}
	}
}

void funcaoCadastroDragao()
{
    Dragao dragon;
	int check = 0;
	int i;
    
    for (i = 0; i < retornaTamanhoElementos(); i++)
    {
    	Elemento* element = obterElementoPeloIndice(i);
    	if (element->codigo > 0)
		{
		
			fflush(stdin);
			printf("Digite o nome do dragao: ");
		    scanf("%[^\n]s", dragon.nome);
		
		    printf("Digite a idade do dragao: ");
		    scanf("%d", &dragon.idade);
		    
		    listarElementos();
		    printf("Digite o codigo do elemento do dragao: ");
		    scanf("%d", &dragon.codigoElemento);

		    printf("Digite o valor do dragao: ");
		    scanf("%f", &dragon.valor);
		    
		    printf("Digite a quantidade em estoque do dragao: ");
		    scanf("%d", &dragon.unidade);
		
		    if (salvarDragao(dragon) == 1)
		        printf("Dragao cadastrado com sucesso!\n");
		    else
		        printf("Falha ao cadastrar dragao!\n");
		        
		    check++;
		    
		    free(element);//falta free em v�rias fun��es depois de chamar obterElementoPeloIndice
		        
		    break;
		}			
	}
	if (check == 0) printf("CADASTRE PELO MENOS UM ELEMENTO ANTES DE CADASTRAR UM DRAGAO\n");

}

void funcaoPesquisarDragao()
{
    char procurado[30];
    int i;

    fflush(stdin);
    printf("Digite o nome do dragao: ");
	scanf("%[^\n]s", procurado);
	Dragao* dragon = obterDragaoPeloNome(procurado);
	Elemento* element = obterElementoPeloCodigo(dragon->codigoElemento);
	
	if (dragon == NULL)
		printf("Nenhum dragao com este nome encontrado\n");
	else{
		printf("O codigo do dragao eh: %d\n", dragon->codigo);
        printf("Sua idade eh: %d\n", dragon->idade);
        printf("Seu elemento eh: %s\n", element->nome);
        printf("Seu valor eh: %f\n", dragon->valor);
        printf("Seu estoque eh: %d\n", dragon->unidade);
	}
	free(dragon);
}

void funcaoExcluirDragao()
{
    listarDragoes();
    int codigo;
    printf("Digite o codigo do dragao que deseja APAGAR: ");
	scanf("%d", &codigo);

	int r = ApagarDragaoPeloCodigo(codigo);
	if (r==1)
		printf("Dragao APAGADO com sucesso!\n");
	else if (r==2)
		printf("Nenhum dragao com esse codigo foi encontrado\n");
	else if (r==3)
		printf("Para ser apagado do sistema o dragao deve ser devolvido antes!\n");
	else
		printf("Falha ao apagar o dragao!\n");
}

void alterarDragoes()
{
	int i, opcao, r, mudancaInt;
	char mudanca[30];
	listarDragoes();
	int codigo;
	printf("Digite o codigo do dragao que deseja alterar: ");
	scanf("%d", &codigo);
	
	do
	{
	printf("\n0 - Finalizar\n1 - Alterar nome\n2 - Alterar idade\n3 - Alterar elemento\n4 - Alterar valor\n5 - Alterar Unidades\n");
	printf("Digite a numero do que deseja alterar: ");
	scanf("%d", &opcao);
	
	if (opcao == 0)
	{
		printf("Finalizado!\n");
		break;
	}
	else if (opcao == 1)
	{
		printf("Digite o novo nome: ");
		fflush(stdin);
		scanf("%[^\n]s", mudanca);
		r = atualizarDragao(0, mudanca, 30, 1, codigo);
	}
	else if (opcao == 2)
	{
		printf("Digite a nova idade: ");
		scanf("%d", &mudancaInt);
		r = atualizarDragao(mudancaInt, mudanca, 30, 2, codigo);
	}
	else if (opcao == 3)
	{
		listarElementos();
		printf("Digite o codigo do novo elemento: ");
		scanf("%d", &mudancaInt);
		if (mudancaInt > QuantidadeElementos() || mudancaInt < 0)
			r = 1;
		else r = atualizarDragao(mudancaInt, mudanca, 30, 3, codigo);
	}
	else if (opcao == 4)
	{
		printf("Digite o novo valor: ");
		scanf("%d", &mudancaInt);
		r = atualizarDragao(mudancaInt, mudanca, 30, 4, codigo);
	}
	else if (opcao == 5)
	{
		printf("Digite o novo estoque: ");
		scanf("%d", &mudancaInt);
		r = atualizarDragao(mudancaInt, mudanca, 30, 5, codigo);
	}
	else printf("Numero invalido!n");

	if (r == 0) printf("Informacao alterada com sucesso");
	else printf("Erro ao alterar informacao");
	
			
	} while (opcao != 0);
		
}

//ELEMENTOS



void funcaoCadastroElemento()
{
    Elemento element;
    

	element.codigo = QuantidadeElementos() + 1;

	fflush(stdin);
	printf("Digite o nome do elemento: ");
    scanf("%[^\n]s", element.nome);

	fflush(stdin);
    printf("Digite a vulnerabilidade do elemento: ");
    scanf("%[^\n]s", element.vulnerabilidade);

    if (salvarElemento(element) == 1)
        printf("Elemento cadastrado com sucesso!\n");
    else
        printf("Falha ao cadastrar elemento!\n");
}

void funcaoPesquisarElemento()
{
    char procurado[30];
    int i;

    fflush(stdin);
    printf("Digite o nome do elemento : ");
	scanf("%[^\n]s", procurado);
    Elemento* element = obterElementoPeloNome(procurado);
        if (element == NULL) 
				printf("Nenhum elemento com este nome encontrado\n");
    	else
		{
            printf("O codigo do elemento eh %d\n", element->codigo);
            printf("Sua vulnerabilidade eh: %s\n", element->vulnerabilidade);
            printf("Seu codigo eh: %d\n", element->codigo);
			
        }
        free(element);
}

void funcaoExcluirElemento()
{
    listarElementos();
    int codigo;
    printf("Digite o codigo do elemento  que deseja APAGAR: ");
	scanf("%d", &codigo);

	int r = ApagarElementoPeloCodigo(codigo);
	if (r==1)
		printf("Elemento APAGADO com sucesso!\n");
	else if (r==2)
		printf("Nenhum elemento com esse codigo foi encontrado\n");
	else if (r==3)
		printf("Um dragao esta usando esse codigo, eh preciso apaga-lo antes\n");
	else
		printf("Falha ao apagar o elemento !\n");
}

void alterarElementos()
{
	int i, opcao, r;
	char mudanca[30];
	listarElementos();
	int codigo;
	printf("Digite o codigo do elemento que deseja alterar: ");
	scanf("%d", &codigo);
	
	do
	{
	printf("\n0 - Finalizar\n1 - Alterar nome\n2 - Alterar vulnerabilidade\n");
	printf("Digite a numero do que deseja alterar: ");
	scanf("%d", &opcao);
	
	if (opcao == 0)
	{
		printf("Finalizado!\n");
		break;
	}
	else if (opcao == 1)
	{
		printf("Digite o novo nome: ");
		fflush(stdin);
		scanf("%[^\n]s", mudanca);
		r = atualizarElemento(mudanca, 30, 1, codigo);
	}
	else if (opcao == 2)
	{
		printf("Digite a nova vulnerabilidade: ");
		fflush(stdin);
		scanf("%[^\n]s", mudanca);
		r = atualizarElemento(mudanca, 30, 2, codigo);
	}
	else printf("Numero invalido!n");

	if (r == 0) printf("Informacao alterada com sucesso");
	else printf("Erro ao alterar informacao");
	
			
	} while (opcao != 0);
		
}


//LOCACOES

void listarLocacoes()
{
	int i;

	if (QuantidadeLocacoes() == 0)
    {
        printf("NENHUMA LOCACAO REALIZADA\n");
    }
    else
	{
		for (i = 0; i < QuantidadeLocacoes(); i++)
		{
			Locacao* location = obterLocacaoPeloIndice(i);
			if (location->codigoLocacao > 0)
			{
				Guerreiro* warrior = obterGuerreiroPeloCodigo(location->codigoGuerreiroLocador);
				Dragao* dragon = obterDragaoPeloCodigo(location->codigoDragaoLocado);	
				printf("\n%d - %d unidades de %s, locado por: %s pela bagatela de %.2f dinheiros diarios | inicio da locacao: %s | fim da locacao: %s\n\n",
				location->codigoLocacao, location->quantidadeLocada, dragon->nome, 
				warrior->nome, location->valorDiario, location->dataInicio, location->dataFim);
				free(location);
		    }
		}
	}
}

void funcaoRealizarLocacao()
{
	int opcao;
    Locacao location;
    int quantidade;

	
	listarGuerreiros();
	printf("Digite o codigo do guerreiro: ");
    scanf("%d", &location.codigoGuerreiroLocador);

    
	listarDragoes();
    printf("Digite o codigo do dragao: ");
    scanf("%d", &location.codigoDragaoLocado);


	printf("Digite quantos dragoes quer locar: ");
	scanf("%d", &quantidade);

    
	int r = salvarLocacao(location, location.codigoDragaoLocado, location.codigoGuerreiroLocador, quantidade);
    
	if (r == 1)
        printf("Locacao realizada com sucesso!\n");
	else if (r == 2)
        printf("Quantidade invalida!\n");
    else
        printf("Falha ao realizar locacao!\n");
}

void funcaoDevolverDragao()
{
    listarLocacoes();
    int codigo;
	if (QuantidadeLocacoes() == 0)
	{}
	else
	{
		printf("Digite o codigo da locacao que quer devolver: ");
		scanf("%d", &codigo);
		if (DevolverLocacaoPeloCodigo(codigo) == 1)
			printf("Locacao devolvida com sucesso!\n");
		else if(DevolverLocacaoPeloCodigo(codigo) == 2)
			printf("Locacao ja devolvida!\n");
		else
			printf("Falha ao devolver a locacao!\n");
	}
}

void funcaoPesquisarLocacao()
{
    char codigo;
    int i;

    fflush(stdin);
    printf("Digite o codigo da locacao: ");
	scanf("%d", &codigo);
	Locacao* location = obterLocacaoPeloCodigo(codigo);
	Guerreiro* warrior = obterGuerreiroPeloCodigo(location->codigoGuerreiroLocador);
	Dragao* dragon = obterDragaoPeloCodigo(location->codigoDragaoLocado);
	Elemento* element = obterElementoPeloCodigo(dragon->codigoElemento);
	if (location == NULL)
		printf("Nenhuma locacao com este codigo encontrada");
	else{
        printf("Nome do guerreiro: %s\n", warrior->nome);
        printf("Titulo do guerreiro: %s\n", warrior->titulo);
        printf("Nome do dragao: %s\n", dragon->nome);
        printf("Elemento do dragao: %s\n", element->nome);
        printf("Quantidade locada: %d\n", location->quantidadeLocada);
        printf("Valor diario da locacao: %.2f\n", location->valorDiario);
        
        free(location);
        free(warrior);
        free(dragon);
        free(element);
	}
}

void ApagarLocacao()
{
	listarLocacoes();
	int codigo, r;
	if (QuantidadeLocacoes() == 0)
	{}
	else
	{
		printf("Digite o codigo da locacao que quer apagar do sistema\n");
		scanf("%d", &codigo);
		r = ExcluirLocacao(codigo);
		if (r == 0)
			printf("Nao eh possivel excluir locacoes nao devolvidas\n");
		else if (r == 1)
		printf("Nenhuma locacao com esse codigo foi encontrada\n");
		else 
			printf("Locacao apagada com sucesso\n");
	}
}



//MENUS	
	
void menuPrincipal()
{
	printf("0 - Sair\n1 - Guerreiros\n2 - Dragoes\n3 - Elementos de dragoes\n4 - Locacoes\n\n");
}
void subMenuGuerreiro()
{
	printf("0 - Sair\n1 - Cadastrar\n2 - Pesquisar\n3 - Excluir\n4 - Listar Guerreiros\n5 - Alterar guerreiro\n\n");
}

void subMenuDragao()
{
	printf("0 - Sair\n1 - Cadastrar\n2 - Pesquisar\n3 - Excluir\n4 - Listar Dragoes\n5 - Alterar dragao\n\n");
}

void subMenuElemento()
{
	printf("0 - Sair\n1 - Cadastrar\n2 - Pesquisar\n3 - Excluir\n4 - Listar Elementos\n5 - Alterar elemento\n\n");	
}

void subMenuLocacao()
{
	printf("0 - Sair\n1 - Locar Dragao\n2 - Pesquisar\n3 - Devolver\n4 - Listar Locacoes\n5 - Excluir Locacao\n\n");	
}

int main(int argc, char *argv[]){
	int opcao;
	//horario do sistema
	struct tm *tempo;
	time_t segundos;
	time(&segundos); 
	tempo = localtime(&segundos);  
	printf("%d/%d/%d\n", tempo->tm_mday, tempo->tm_mon+1, tempo->tm_year+1900);
	printf("%d:%d:%d\n", tempo->tm_hour, tempo->tm_min, tempo->tm_sec);

	if (inicializarGuerreiros() == 0 || inicializarDragoes() == 0 || inicializarElementos() == 0 || inicializarLocacoes() == 0)
	{
		printf("Erro de alocacao dinamica!");
		return 0;
	}

    printf("-------------------\n");
    printf("LOCADORA DA KAHLEESI\n");
    printf("-------------------\n");
    do
    {
		menuPrincipal();
        scanf("%d", &opcao);
        if (opcao == 0)
        {
            printf("Obrigado por utilizar este programa!");
            break;
        }

        if (opcao == 1)//Guerreiros
        {
        	while (opcao != 0)
        	{
	        		
				subMenuGuerreiro();
				scanf("%d", &opcao);
				
	            if (opcao == 0){}
	
				else if (opcao == 1)
					funcaoCadastroGuerreiro();
				else if (opcao == 2)
	            {
					funcaoPesquisarGuerreiro();
	            }
				else if (opcao == 3)
	            {
					funcaoExcluirGuerreiro();
	            }
	            else if (opcao == 4)
	            {
	                listarGuerreiros();
	            }
	            else if (opcao == 5)
	            {
	            	alterarGuerreiros();
				}
				else
					printf("Opcao invalida");
			}
			opcao = 1;
			
        }
        
        if (opcao == 2)// Dragoes
        {
        	while (opcao != 0)
        	{
	        	subMenuDragao();
				scanf("%d", &opcao);
				
	            if (opcao == 0){}
	
				else if (opcao == 1)
					funcaoCadastroDragao();
				else if (opcao == 2)
	            {
					funcaoPesquisarDragao();
	            }
				else if (opcao == 3)
	            {
					funcaoExcluirDragao();
	            }
	            else if (opcao == 4)
	            {
	                listarDragoes();
	            }
				else if (opcao == 5)
				{
					alterarDragoes();
				}
				else
					printf("Opcao invalida");
			}
			opcao = 1;
		}

        if (opcao == 3)// Elementos
        {
        	while (opcao != 0)
        	{
	        	subMenuElemento();
				scanf("%d", &opcao);
				
	            if (opcao == 0){}
	
				else if (opcao == 1)
					funcaoCadastroElemento();
				else if (opcao == 2)
	            {
					funcaoPesquisarElemento();
	            }
				else if (opcao == 3)
	            {
					funcaoExcluirElemento();
	            }
	            else if (opcao == 4)
	            {
	                listarElementos();
	            }
	            else if (opcao == 5)
	            {
	                alterarElementos();
	            }
				else
					printf("Opcao invalida");
			}
			opcao = 1;
		}
		
        if (opcao == 4)// Locacoes
        {
        	while (opcao != 0)
        	{
	        	subMenuLocacao();
				scanf("%d", &opcao);
				
	            if (opcao == 0){}
	
				else if (opcao == 1)
					funcaoRealizarLocacao();
				else if (opcao == 2)
	            {
					funcaoPesquisarLocacao();
	            }
				else if (opcao == 3)
	            {
					funcaoDevolverDragao();
	            }
				else if (opcao == 4)
	            {
					listarLocacoes();
	            }
	            else if (opcao == 5)
	            {
					ApagarLocacao();
	            }
				else
					printf("Opcao invalida");
			}
		}
		
		opcao = 1;
    } while(opcao != 0);
    encerraGuerreiros();
    encerraDragoes();
    encerraElementos();
    encerraLocacoes();
	return 0;
}
