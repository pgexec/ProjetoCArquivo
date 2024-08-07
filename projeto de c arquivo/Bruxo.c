#include "Bruxo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


FILE* bruxos;
int qtdBruxos;


int InicializarBruxos()
{
	bruxos = fopen("bruxos.bin", "r+b");
	if(bruxos == NULL)
	{
		return 0;
	}
	qtdBruxos = quantidade_bruxo_ini();

	
	return 1;
}


int EncerraBruxos()
{
	fclose(bruxos);
	bruxos = NULL;
	return 1;	
}

int quantidade_bruxo_ini()
{
	fseek(bruxos,0,SEEK_END);
	size_t tam = ftell(bruxos);
	int qtd = tam/ sizeof(Bruxo);
	fseek(bruxos,0,SEEK_SET);
	return qtd;
}



int SalvarBruxo(Bruxo novo)
{	
	fseek(bruxos,0,SEEK_END);	
	size_t resultado = fwrite(&novo,sizeof(Bruxo),1,bruxos);
	if( resultado != 1)
	{
		return 0;
	}
	qtdBruxos++;
	return 1;
}


int QuantidadeBruxos()
{
	return qtdBruxos;
}



Bruxo* ObterBruxoPeloIndice(int indice)
{
	Bruxo* novo = (Bruxo*) malloc (1 * sizeof(Bruxo));
	if(novo == NULL)
	{
		return NULL;
	}
	size_t tamanho = sizeof(Bruxo);
	int deslocamento = indice * tamanho;
	fseek(bruxos,deslocamento,SEEK_SET);
	fread(novo,tamanho, 1,bruxos);

	return novo;	
}



Bruxo* ObterBruxoPeloCodigo(int codigo)
{
	Bruxo* novo = (Bruxo *) malloc(1 * sizeof(Bruxo));
	if(novo == NULL)
	{
		return NULL;	
	}
	
	size_t tamanho = sizeof(Bruxo);
	
	for(int i = 0; i < qtdBruxos; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(bruxos, deslocamento, SEEK_SET);
		
		fread(novo,tamanho,1,bruxos);
		
		if(novo->codigo == codigo)
		{
			return novo;	
		}
	}
	
	free(novo);
	return NULL;
}



int AtualizarBruxo(Bruxo bruxo_att)
{	
	Bruxo* buffer_bruxo = (Bruxo*) malloc(1 *sizeof(Bruxo));
	if(buffer_bruxo == NULL)
	{
		return 0;
	}
	
	size_t tamanho = sizeof(Bruxo); 
	
	for(int i = 0; i < qtdBruxos; i++)
	{
		int deslocamento = i * sizeof(Bruxo);
		
		fseek(bruxos, deslocamento, SEEK_SET);
		fread(buffer_bruxo, sizeof(Bruxo),1, bruxos);
		
		if(buffer_bruxo->codigo == bruxo_att.codigo)
		{
			fseek(bruxos,-tamanho, SEEK_CUR);		
			*buffer_bruxo = bruxo_att;
			fwrite(buffer_bruxo,tamanho, 1, bruxos);
			return 1;
		}
	}
	free(buffer_bruxo);
	return 0;
	
}
	


int ApagarBruxoPeloCodigo(int codigo)
{
	Bruxo* buffer_bruxo = (Bruxo* ) malloc (1 * sizeof(Bruxo));
	if(buffer_bruxo == NULL)
	{
		return 0;
	}
	
	FILE* arqv_bruxo = fopen("bruxos_apagar.bin","wb");
	if(arqv_bruxo == NULL)
	{
		free(buffer_bruxo);
		return 0;
	}
	
	
	
	
	for(int i = 0; i < qtdBruxos; i++)
	{
		int deslocamento = i * sizeof(Bruxo);
		
		fseek(bruxos, deslocamento, SEEK_SET);
		fread(buffer_bruxo, sizeof(Bruxo),1, bruxos);
		
		if(buffer_bruxo->codigo != codigo)
		{
			fwrite(buffer_bruxo,sizeof(Bruxo),1,arqv_bruxo);
		}	
	}
	fclose(bruxos);
	fclose(arqv_bruxo);
	
	
	if(remove("bruxos.bin"))
	{
		return 0;
	}
	if(rename("bruxos_apagar.bin","bruxos.bin"))
	{
		return 0;
	}
	
	free(buffer_bruxo);
	InicializarBruxos();

	return 1;
}



int ApagarBruxoPeloNome(char* nome)
{
	
}

