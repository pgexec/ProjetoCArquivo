#include "Pocao.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


FILE* pocoes;
int qtdPocoes;



int InicializarPocoes()
{
	 pocoes = fopen("pocoes.bin", "r+b");
	if(pocoes == NULL)
	{
		return 0;
	}
	qtdPocoes =  quantidade_pocoes_ini();
	return 1;
}

int quantidade_pocoes_ini()
{
	fseek(pocoes,0,SEEK_END);
	size_t tam = ftell(pocoes);
	int qtd = tam/ sizeof(Pocao);
	fseek(pocoes,0,SEEK_SET);
	return qtd;
}



int EncerraPocoes()
{
	fclose(pocoes);
	pocoes = NULL;
	return 1;	 
}




int SalvarPocao(Pocao novo) 
{
	fseek(pocoes,0,SEEK_END);	
	size_t resultado = fwrite(&novo,sizeof(Pocao),1,pocoes);
	if( resultado != 1)
	{
		return 0;
	}
	qtdPocoes++;
	return 1;	
}





int QuantidadePocoes()
{
	return qtdPocoes;
 }

Pocao* ObterPocaoPeloIndice(int indice)
{
	Pocao* novo = (Pocao*) malloc (1 * sizeof(Pocao));
	if(novo == NULL)
	{
		return NULL;
	} 
	size_t tamanho = sizeof(Pocao);
	int deslocamento = indice * tamanho;
	fseek(pocoes,deslocamento,SEEK_SET);
	fread(novo,tamanho, 1,pocoes);

	return novo;	
 
}




Pocao* ObterPocaoPeloCodigo(int codigo)
{
  Pocao* novo = (Pocao *) malloc(1 * sizeof(Pocao));
	if(novo == NULL)
	{
		return NULL;	
	}
	size_t tamanho = sizeof(Pocao);
	
	for(int i = 0; i < qtdPocoes; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(pocoes, deslocamento, SEEK_SET);
		
		fread(novo,tamanho,1,pocoes);
		
		if(novo->codigo == codigo)
		{
			return novo;	
		}
	}
	free(novo);	
	return NULL;
}





int AtualizarPocao(Pocao pocao_att){ 

	Pocao* buffer_pocao = (Pocao*) malloc(1 *sizeof(Pocao));
	if(buffer_pocao == NULL)
	{
		return 0;
	}
	

	size_t tamanho = sizeof(Pocao); 
	
	for(int i = 0; i < qtdPocoes; i++)
	{
		int deslocamento = i * sizeof(Pocao);
		
		fseek(pocoes, deslocamento, SEEK_SET);
		
		fread(buffer_pocao, sizeof(Pocao),1, pocoes);
		
		if(buffer_pocao->codigo == pocao_att.codigo)
		{
			fseek(pocoes,-tamanho, SEEK_CUR);
					
			*buffer_pocao = pocao_att;
			fwrite(buffer_pocao,sizeof(Pocao), 1, pocoes);
			return 1;
		}
	}
	free(buffer_pocao);		
}





int ApagarPocaoPeloCodigo(int codigo)
{
		Pocao* buffer_pocao = (Pocao* ) malloc (1 * sizeof(Pocao));
	if(buffer_pocao == NULL)
	{
		return 0;
	}
	
	FILE* arqv_pocao = fopen("pocao_apagar.bin","wb");
	if(arqv_pocao == NULL)
	{
		return 0;
	}
	
	
	for(int i = 0; i < qtdPocoes; i++)
	{
		int deslocamento = i * sizeof(Pocao);
		
		fseek(pocoes, deslocamento, SEEK_SET);
		fread(buffer_pocao, sizeof(Pocao),1, pocoes);
		
		if(buffer_pocao->codigo != codigo)
		{
			fwrite(buffer_pocao,sizeof(Pocao),1,arqv_pocao);
		}	
	}
	
	fclose(pocoes);
	fclose(arqv_pocao);
	
	
	if(remove("pocoes.bin"))
	{
		return 0;
	}
	if(rename("pocao_apagar.bin","pocoes.bin"))
	{
		return 0;
	}
	
	free(buffer_pocao);
	InicializarPocoes();

	return 1;	 
}





int ApagarPocaoPeloNome(char* nome){ }

