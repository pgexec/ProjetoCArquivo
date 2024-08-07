#include "Paciente.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FILE* pacientes;
int qtdPacientes;




int InicializarPacientes()
{
	pacientes = fopen("paciente.bin", "r+b");
	if(pacientes == NULL)
	{
		return 0;
	}
	qtdPacientes = quantidade_pacientes_ini();
	return 1;
}

int quantidade_pacientes_ini()
{
	fseek(pacientes,0,SEEK_END);
	size_t tam = ftell(pacientes);
	int qtd = tam/ sizeof(Paciente);
	fseek(pacientes,0,SEEK_SET);
	return qtd;
}




int EncerraPacientes()
{
	fclose(pacientes);
	pacientes = NULL;
	return 1;
}



int SalvarPaciente(Paciente novo)
{
	fseek(pacientes,0,SEEK_END);	
	size_t resultado = fwrite(&novo,sizeof(Paciente),1,pacientes);
	if( resultado != 1)
	{
		return 0;
	}
	qtdPacientes++;
	return 1;
}




int QuantidadePacientes()
{
	return qtdPacientes;
}




Paciente* ObterPacientePeloIndice(int indice)
{
	Paciente* novo = (Paciente*) malloc (1 * sizeof(Paciente));
	if(novo == NULL)
	{
		return NULL;
	}
	size_t tamanho = sizeof(Paciente);
	int deslocamento = indice * tamanho;
	fseek(pacientes,deslocamento,SEEK_SET);
	fread(novo,tamanho, 1,pacientes);
	
	return novo;
}





Paciente* ObterPacientePeloCodigo(int codigo)
{
	Paciente* novo = (Paciente *) malloc(1 * sizeof(Paciente));
	if(novo == NULL)
	{
		return NULL;	
	}
	
	size_t tamanho = sizeof(Paciente);
	
	for(int i = 0; i < qtdPacientes; i++)
	{
		int deslocamento = i * tamanho;
		
		fseek(pacientes, deslocamento, SEEK_SET);
		
		fread(novo,tamanho,1,pacientes);
		
		if(novo->codigo == codigo)
		{
			return novo;	
		}
	}
	
	free(novo);
	return NULL;
}




int AtualizarPaciente(Paciente paciente_att)
{
		Paciente* buffer_paciente = (Paciente*) malloc(1 *sizeof(Paciente));
	if(buffer_paciente == NULL)
	{
		return 0;
	}
	
	size_t tamanho = sizeof(Paciente); 
	
	for(int i = 0; i < qtdPacientes; i++)
	{
		int deslocamento = i * sizeof(Paciente);
		
		fseek(pacientes, deslocamento, SEEK_SET);
		fread(buffer_paciente, sizeof(Paciente),1, pacientes);
		
		if(buffer_paciente->codigo == paciente_att.codigo)
		{
			fseek(pacientes,-tamanho, SEEK_CUR);	
				
			*buffer_paciente = paciente_att;
			
			fwrite(buffer_paciente,sizeof(Paciente), 1, pacientes);
			return 1;
		}
	}
	free(buffer_paciente);
	return 0;
	
}




int ApagarPacientePeloCodigo(int codigo)
{
	Paciente* buffer_paciente = (Paciente* ) malloc (1 * sizeof(Paciente));
	if(buffer_paciente == NULL)
	{
		return 0;
	}
	
	FILE* arqv_paciente = fopen("paciente_apagar.bin","wb");
	if(arqv_paciente == NULL)
	{
		return 0;
	}
	
	
	for(int i = 0; i < qtdPacientes; i++)
	{
		int deslocamento = i * sizeof(Paciente);
		
		fseek(pacientes, deslocamento, SEEK_SET);
		fread(buffer_paciente, sizeof(Paciente),1, pacientes);
		
		if(buffer_paciente->codigo != codigo)
		{
			fwrite(buffer_paciente,sizeof(Paciente),1,arqv_paciente);
		}	
	}
	
	fclose(pacientes);
	fclose(arqv_paciente);
	
	
	if(remove("paciente.bin"))
	{
		return 0;
	}
	if(rename("paciente_apagar.bin","paciente.bin"))
	{
		return 0;
	}
	
	free(buffer_paciente);
	InicializarPacientes();
	return 1;	
}

int ApagarPacientePeloNome(char* nome)
{
	
}

