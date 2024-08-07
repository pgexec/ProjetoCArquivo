#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tratamento.h"




FILE* tratamentos;
int qtdTratamentos;


int InicializarTratamento(void)
{
	tratamentos = fopen("tratamentos.bin","r+b");
	if(tratamentos == NULL)
	{
		return 0;
	}
	qtdTratamentos = quantidade_tratamentos_ini();
	
	return 1;	
}

int quantidade_tratamentos_ini()
{
	fseek(tratamentos,0,SEEK_END);
	size_t tam = ftell(tratamentos);
	int qtd = tam/ sizeof(Tratamento);
	fseek(tratamentos,0,SEEK_SET);
	return qtd;
}




int SalvarTratamento(Tratamento novo)
{
	fseek(tratamentos,0,SEEK_END);	
	size_t resultado = fwrite(&novo,sizeof(Tratamento),1,tratamentos);
	if( resultado != 1)
	{
		return 0;
	}
	qtdTratamentos++;
	return 1;
}





int EncerraTratamento()
{
	fclose(tratamentos);
	return 1;
}





int QuantidadeTratamento()
{
	return qtdTratamentos;
}




Tratamento* ObterTratamentoPeloIndice(int indice)
{
	Tratamento* novo = (Tratamento*) malloc (1 * sizeof(Tratamento));
	if(novo == NULL)
	{
		return NULL;
	}
	
	size_t tamanho = sizeof(Tratamento);
	int deslocamento = indice * tamanho;
	fseek(tratamentos,deslocamento,SEEK_SET);

	fread(novo,tamanho, 1,tratamentos);

	return novo;	
		
		
}





Tratamento* ObterTratamentoPacienteCodigo(int codPaciente, int* qtd)
{
	
	Tratamento* buffer_trata = (Tratamento *) malloc(1 * sizeof(Tratamento));
	if(buffer_trata == NULL)
	{
		return NULL;	
	}
	
	size_t tamanho = sizeof(Tratamento);
	int qtdTrata = 0;
	
	
	
	
	for(int i = 0; i < qtdTratamentos; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(tratamentos, deslocamento, SEEK_SET);
		
		fread(buffer_trata,tamanho,1,tratamentos);
		
		if(buffer_trata->Codpaciente == codPaciente)
		{
			qtdTrata++;
		}
	}	
	
	*qtd = qtdTrata;
	
		
	Tratamento* buffer = (Tratamento *) malloc(qtdTrata * sizeof(Tratamento));
	if(buffer == NULL)
	{
		return NULL;
	}
	
	


	
	for(int i = 0; i < qtdTratamentos; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(tratamentos, deslocamento, SEEK_SET);
		
		fread(&buffer[i],tamanho,1,tratamentos);
	
		if(buffer[i].Codpaciente == codPaciente)
		{
			
			return buffer;	
					
		}
			
		
	}
	
	free(buffer_trata);	
	return NULL;
}






Tratamento* ObterTratamentoBruxoCodigo(int codBruxo, int* qtd)
{
		
	Tratamento* buffer_trata = (Tratamento *) malloc(1 * sizeof(Tratamento));
	if(buffer_trata == NULL)
	{
		return NULL;	
	}
	
	size_t tamanho = sizeof(Tratamento);
	int qtdTrata = 0;
	
	
	
	
	for(int i = 0; i < qtdTratamentos; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(tratamentos, deslocamento, SEEK_SET);
		
		fread(buffer_trata,tamanho,1,tratamentos);
		
		if(buffer_trata->Codbruxo == codBruxo)
		{
			qtdTrata++;
		}
	}	
	
	*qtd = qtdTrata;
	
		
	Tratamento* buffer = (Tratamento *) malloc(qtdTrata * sizeof(Tratamento));
	if(buffer == NULL)
	{
		return NULL;
	}
	
	


	
	for(int i = 0; i < qtdTratamentos; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(tratamentos, deslocamento, SEEK_SET);
		
		fread(&buffer[i],tamanho,1,tratamentos);
	
		if(buffer[i].Codbruxo == codBruxo)
		{
			
			return buffer;	
					
		}
			
		
	}
	
	free(buffer_trata);
	return NULL;	
}


int AtualizarTratamento(Tratamento tratamento_att)
{
	
	Tratamento* buffer_tratamento = (Tratamento *) malloc (1 * sizeof(Tratamento));
	if(buffer_tratamento == NULL)
	{
		return 0;
	}
	
	size_t tamanho  = sizeof(Tratamento);
	
	
	for(int i = 0; i < qtdTratamentos; i++)
	{
		int deslocamento = i * sizeof(Tratamento);
		
		fseek(tratamentos, deslocamento, SEEK_SET);
		fread(buffer_tratamento, tamanho,1, tratamentos);
	
		if(buffer_tratamento[i].codigo == tratamento_att.codigo)
		{
			buffer_tratamento[i].dias += tratamento_att.dias;
			buffer_tratamento[i].doses += tratamento_att.doses;
			
		
			fseek(tratamentos,-tamanho, SEEK_CUR);	
	
			
			fwrite(buffer_tratamento,sizeof(Tratamento), 1, tratamentos);
			free(buffer_tratamento);
			return 1;
		}		
	}	
	
	free(buffer_tratamento);
	return 0;		
}



int ApagarTratamentosPeloCodigo(int codigo)
{
	
	Tratamento* buffer_tratamento = (Tratamento* ) malloc (1 * sizeof(Tratamento));
	if(buffer_tratamento == NULL)
	{
		return 0;
	}
	
	FILE* arqv_trata = fopen("tratamento_apagar.bin","wb");
	if(arqv_trata == NULL)
	{
		return 0;
	}
	

	
	for(int i = 0; i < qtdTratamentos; i++)
	{
		int deslocamento = i * sizeof(Tratamento);
		
		fseek(tratamentos, deslocamento, SEEK_SET);
		fread(buffer_tratamento, sizeof(Tratamento),1, tratamentos);
		
		if(buffer_tratamento->codigo != codigo)
		{
			fwrite(buffer_tratamento,sizeof(Tratamento),1,arqv_trata);
		}	
	}
	
	
	fclose(tratamentos);
	fclose(arqv_trata);
	
	
	if(remove("tratamentos.bin"))
	{
		return 0;
	}
	if(rename("tratamento_apagar.bin","tratamentos.bin"))
	{
		return 0;
	}
	
	free(buffer_tratamento);
	InicializarTratamento();
	return 1;
}












