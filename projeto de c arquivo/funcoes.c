#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"






void Imprimir_Menu(void)
{
	printf("----------------------\n");
	printf("BEM - VINDO AO MENU PRINCIPAL\n");
	printf("0 - Sair\n");
	printf("1 - Bruxo\n");
	printf("2 - Paciente\n");
	printf("3 - Pocao\n");
	printf("4 - Tratamento\n");	
	printf("digite: ");
	
}

void Imprimir_MenuSub(int opcaoMenu)
{
	
	switch(opcaoMenu)
	{
		case 1:{
			printf("----------------------\n");		
			printf("BEM VINDO AO MENU DO BRUXO!!\n");
			printf("0. Sair\n");
			printf("1. Listar\n");
			printf("2. Cadastrar\n");
			printf("3. Alterar\n");
			printf("4. Excluir\n");
			printf("digite: ");
			break;
		}
		
		case 2:{
			printf("----------------------\n");
			printf("BEM VINDO AO MENU DO PACIENTE!!\n");
			printf("0. Sair\n");
			printf("1. Listar\n");
			printf("2. Cadastrar\n");
			printf("3. Alterar\n");
			printf("4. Excluir\n");
			printf("digite: ");
			break;
		}
		
		case 3:{
			printf("----------------------\n");
			printf("BEM VINDO AO MENU DO POCAO!!\n");
			printf("0. Sair\n");
			printf("1. Listar\n");
			printf("2. Cadastrar\n");
			printf("3. Alterar\n");
			printf("4. Excluir\n");
			printf("digite: ");
			break;
		}
		
		case 4:{
			printf("------------------------------\n");
			printf("BEM VINDO AO MENU TRATAMENTO!!\n");
			printf("0.Sair\n");
			printf("1.Listar tratamentos do paciente\n");
			printf("2.Listar tratamentos do bruxo\n");
			printf("3.Iniciar tratamento\n");
			printf("4.Ampliar tratamento\n");
			printf("5.Excluir tratamento\n");
			printf("digite: ");
			break;
		}
	}
	

	
}

int Listar_TratamentosPaciente(void)
{
	
	int qtdTratamento = 0;
	int codPaciente = codigo(2);
	
	
	Paciente* paciente  = ObterPacientePeloCodigo(codPaciente);
	if(paciente == NULL)
	{
		printf("CODIGO INVALIDO\n");
		return 0;
	}
	
	Tratamento* tratamento = ObterTratamentoPacienteCodigo(codPaciente, &qtdTratamento);
	if(tratamento == NULL)
	{
		free(tratamento);
		return 0;
	}
	
	printf("TRATAMENTOS ENCONTRADOS DO PACIENTE %s\n", paciente->nome);
	free(paciente);
	
	for(int i = 0; i < qtdTratamento; i++)
	{
		Pocao* pocao = ObterPocaoPeloCodigo(tratamento[i].Codpocao);
		if(pocao == NULL)
		{
			free(pocao);
			return 0;
		}
		
		printf("codigo Tratamento: %d\n", tratamento[i].codigo);
		printf("Pocao:%s\n", pocao[i].nome);	
		printf("dias: %d\n", tratamento[i].dias);
		printf("doses: %d\n", tratamento[i].doses);
		free(pocao);
		
	}
	
	free(tratamento);
	return 1;	
}




int Listar_TratamentoBruxo(void)
{
	int qtdTratamento = 0;
	int codBruxo = codigo(1);
	Bruxo* bruxo = ObterBruxoPeloCodigo(codBruxo);
	
	if(bruxo == NULL)
	{
		printf("CODIGO INVALIDO\n");
		return 0;
	}
	
	Tratamento* tratamento = ObterTratamentoBruxoCodigo(codBruxo, &qtdTratamento);
	if(tratamento == NULL)
	{
		return 0;
	}
	
	
	printf("TRATAMENTOS DO %s ENCONTRADOS:\n", bruxo->nome);
	free(bruxo);
	for(int i = 0; i < qtdTratamento; i++)
	{
		Paciente* paciente  = ObterPacientePeloCodigo(tratamento[i].Codpaciente);
		if(paciente == NULL)
		{
			free(paciente);
			return 0;
		}
		Pocao* pocao = ObterPocaoPeloCodigo(tratamento[i].Codpocao);
		if(pocao == NULL)
		{
			free(pocao);
			return 0;
		}
		
		printf("nome:%s\n", paciente[i].nome);
		printf("codigo Tratamento: %d\n", tratamento[i].codigo);
		printf("Pocao:%s\n", pocao->nome);	
		printf("dias: %d\n", tratamento[i].dias);
		printf("doses: %d\n", tratamento[i].doses);
		return 1;
		
		free(pocao);
		free(paciente);	
	}	
	free(tratamento);
	return 0;
}


void Listar (int opcao)
{
	switch(opcao)
	{
		case 1:
		{
			if(QuantidadeBruxos() == 0)
			{
				printf("Nao tem nenhum Bruxo cadastrado!");
			}
			for(int i = 0; i < QuantidadeBruxos(); i++)
			{
				Bruxo* bruxo = ObterBruxoPeloIndice(i);
				printf("----------------------------\n");
				printf("Codigo: %d\n",bruxo->codigo );
				printf("nome: %s\n",bruxo->nome );
				printf("especialidade: %s\n",bruxo->especialidade );
				printf("----------------------------\n");
				free(bruxo);
			}						
			break;
		}
		case 2:{
			
			if(QuantidadePacientes() == 0)
			{
				printf("Nao tem nenhum Paciente cadastrado!");
			}
			
			for(int i = 0; i < QuantidadePacientes(); i++)
			{
				Paciente* paciente = ObterPacientePeloIndice(i);
				printf("----------------------------\n");
				printf("Codigo: %d\n",paciente->codigo );
				printf("nome: %s\n",paciente->nome );
				printf("idade: %d\n",paciente->idade );
				printf("altura: %.2f\n", paciente->altura);
				printf("----------------------------\n");
				free(paciente);
			}
			break;
		}
		
		case 3:
		{
			if(QuantidadePocoes() == 0)
			{
				printf("Nao tem nenhum Pocoes cadastrado!");
			}
			
			for(int i = 0; i < QuantidadePocoes(); i++)
			{
				Pocao* pocao = ObterPocaoPeloIndice(i);
				printf("----------------------------\n");
				printf("Codigo: %d\n",pocao->codigo );
				printf("nome: %s\n",pocao->nome );
				printf("tipo: %s\n",pocao->tipo);
				printf("----------------------------\n");
				free(pocao);				
			}

		}
	}
	
	
}

int indice_bruxo(void)
{
	int indice;
	printf("qual é o indice do bruxo:");
	scanf("%d", &indice);
	return indice;
}



int codigo(int codigo)
{
	switch(codigo)
	{
		case 1:{
			printf("qual e o codigo do bruxo: ");
			scanf("%d", &codigo);
			return codigo;
			break;
		}
		case 2:{
			printf("qual e o codigo do Paciente: ");
			scanf("%d", &codigo);
			return codigo;
			break;
		}
		case 3:{
			printf("qual e o codigo do Pocao: ");
			scanf("%d", &codigo);
			return codigo;
			break;
		}
		case 4:{
			printf("qual e o codigo de tratamento: ");
			scanf("%d", &codigo);
			return codigo;
			break;
		}
	}
	
}


int verificador_bruxo(int codigo)
{
	int qtd;
	Tratamento* tratamento = ObterTratamentoBruxoCodigo(codigo, &qtd);
	if(tratamento == NULL)
	{
		
		return 0;
	}
	printf("Esse bruxo está em tratamento!");
	free(tratamento);
	return 1;
}



int verificador_paciente(int codigo)
{
	int qtd;
	Tratamento* tratamento = ObterTratamentoPacienteCodigo(codigo, &qtd);
	if(tratamento == NULL)
	{
		free(tratamento);
		return 0;
	}
	printf("Esse Paciente está em tratamento!");
	free(tratamento);
	
	return 1;
}




int verificador_pocao(int codigo)
{	
	Tratamento* trata;

	for( int i = 0; i < QuantidadeTratamento(); i++)
	{
		trata = ObterTratamentoPeloIndice(i);	
		if(trata->Codpocao == codigo)
		{
			free(trata);
			return 1;
		}
		
		if(trata == NULL)
		{
			free(trata);
		}
	}
	
	return 0;
}


int verificador_CodigoTratamento(int codigo)
{	
	
	
	for( int i = 0; i < QuantidadeTratamento(); i++)
	{
		Tratamento *tratamento = ObterTratamentoPeloIndice(i);
		if(tratamento == NULL)
		{
			printf("NULL\n");	
		}
			
		if(tratamento->codigo == codigo)
		{
			
			free(tratamento);
			return 1;
		}
	}
	
	return 0;
} 






int verifica_BruxoExiste(int codigo)
{
	Bruxo* bruxo; 
	
	for(int i = 0; i < QuantidadeBruxos(); i++)
	{
		bruxo = ObterBruxoPeloIndice(i);
		if(bruxo->codigo == codigo)
		{
			free(bruxo);
			return 1;
		}
	}
	free(bruxo);
	printf("Codigo invalido de Bruxo!\n");
	return 0;
}



int verifica_PacienteExiste(int codigo)
{
	Paciente* paci;
	
	for(int i = 0; i < QuantidadePacientes(); i++)
	{
		paci = ObterPacientePeloIndice(i);
		if(paci->codigo == codigo);
		{
			free(paci);
			return 1;
		}
	}
	free(paci);
	printf("Codigo invalido de Paciente\n!");
	return 0;
}



int verifica_PocaoExiste(int codigo)
{
	Pocao* pocao;
	
	for(int i = 0; i < QuantidadePocoes(); i++)
	{
		pocao = ObterPocaoPeloIndice(i);
		if(pocao->codigo == codigo)
		{
			free(pocao);
			return 1;
		}
	}
	printf("Codigo invalido de Pocao!\n");
	free(pocao);
	return 0;
}






Bruxo infos_cadastro(void)
{
	Bruxo novo;
	printf("digite o nome do seu bruxo: ");
	scanf(" %[^\n]",novo.nome );
	printf("digite um codigo: ");
	scanf("%d", &novo.codigo);
	printf("qual a e specialidade do bruxo: ");
	scanf(" %[^\n]", novo.especialidade);
	
	return novo;
}





Pocao info_cadastroPocao(void)
{
	Pocao novo;
	printf("digite o nome da sua pocao: ");
	scanf(" %s", novo.nome );
	printf("digite um codigo: ");
	scanf("%d", &novo.codigo);
	printf("qual é o tipo da sua pocao: ");
	scanf(" %s", novo.tipo);
	return novo;
}




Paciente info_cadastroPaciente(void)
{
	Paciente novo;
	printf("digite o nome do paciente: ");
	scanf(" %[^\n]", novo.nome );
	printf("digite um codigo: ");
	scanf("%d", &novo.codigo);
	printf("qual e a altura: ");
	scanf("%f", &novo.altura);
	printf("qual e a idade: ");
	scanf("%d", &novo.idade);
	return novo;
}




Bruxo alterar_bruxo(void)
{
	Bruxo novo;
	printf("------------------------\n");
	printf("qual o codigo do bruxo:");
	scanf("%d", &novo.codigo);
	printf("digite o novo nome:  ");
	scanf("%s", novo.nome);
	printf("digite a nova especialidade: ");
	scanf("%s", novo.especialidade);
	
	
	return novo;
}





Pocao alterar_Pocao(void)
{
	Pocao novo;
	printf("------------------------\n");
	printf("qual o codigo da sua pocao:");
	scanf("%d", &novo.codigo);
	printf("digite o novo nome: ");
	scanf("%s", novo.nome);
	printf("digite a novo tipo: ");
	scanf("%s", novo.tipo);
	return novo;
}




Paciente alterar_Paciente(void)
{
	Paciente novo;
	printf("------------------------\n");
	printf("qual o codigo do Paciente:");
	scanf("%d", &novo.codigo);
	printf("digite o novo nome: ");
	scanf("%s", novo.nome);
	printf("digite a nova idade: ");
	scanf("%d", &novo.idade);
	printf("digite a nova altura: ");
	scanf("%f", &novo.altura);
	
	return novo;
}

 Tratamento alterar_tratamento(void)
 {
 	Tratamento novo;
	printf("------------------------\n");
	printf("qual o codigo do Tratamento:");
	scanf("%d", &novo.codigo);
	printf("digite quantos dias a mais: ");
	scanf("%d", &novo.dias);
	printf("digite quantas dosagens a mais: ");
	scanf("%d", &novo.doses);
	
	return novo;
 }







 int validacao_opcao(int opcao)
 {
 	if(opcao < 0 || opcao > 4)
 	{
		return 0; 
	}
	else 
	{
		return 1;
	}
 }
 
 
 int validacao_opcaoTratamento(int opcao)
 {
 	if(opcao < 0 || opcao > 5)
 	{
		return 0; 
	}
	else 
	{
		return 1;
	}
 }
 
 
 
 
 void Menu_tratamento(void)
 {
	int opcaoTratamento = 0;
	int imprimir = 4;
	do
	{
		Imprimir_MenuSub(imprimir);
		scanf("%d", &opcaoTratamento);
		if( validacao_opcaoTratamento(opcaoTratamento) != 0)
		{
			switch(opcaoTratamento)
			{
				case 1:{
					if(Listar_TratamentosPaciente() == 0)
					{
						printf("não encontramos tratamentos");
					}
					break;
				}
				
				case 2:{
					
					if(Listar_TratamentoBruxo() == 0)
					{
						printf("não encontramos tratamentos");
					}
					break;
				}
				case 3:{
					
					Tratamento novo = infos_tratamento();
					if(verificador_CodigoTratamento(novo.codigo) != 0)
						{
							printf("O codigo de tratamento ja existe, coloque outro!!");
							break;
						}					
					if( verifica_PocaoExiste(novo.Codpocao) != 0 || verifica_BruxoExiste(novo.Codbruxo) != 0 || verifica_PacienteExiste(novo.Codpaciente) != 0)
					{
						
					
						if(SalvarTratamento(novo) != 0)
						{
						
							printf("salvo com sucesso!\n");
						
						}
						else
						{
							printf("erro ao salvar!\n");
						}
					
					}
					else
					{
						printf("codigo não existe");
					}
						
					break;
				}
				case 4:{
					Tratamento novo = alterar_tratamento();
					if(verificador_CodigoTratamento(novo.codigo) == 0)
					{
						printf("Este codigo de tratamento nao existe\n");
						break;
					}
					
					if(AtualizarTratamento(novo) != 0)
					{
						printf("salvo com sucesso!\n");
					}
					else
					{
						printf("erro ao salvar!\n");	
					}
					break;
				}
				case 5:{
					int codigotrata = codigo(4);
					if(verificador_CodigoTratamento(codigotrata) == 0)
					{
						printf("Este codigo de tratamento nao existe\n");
						break;
					}
					
					if(ApagarTratamentosPeloCodigo(codigotrata) != 0)
					{
						printf("excluido com sucesso!");
						break;
					}
					else
					{
						printf("erro ao excluir!");
					}
					break;
				}
			}
		}
		else
		{
			printf("digite um numero valido!");	
		}
		
	}
	while(opcaoTratamento != 0);
	
 }
 
Tratamento infos_tratamento(void)
{
	Tratamento novo;
	printf("qual será o codigo desse tratamento: ");
	scanf("%d", &novo.codigo);
	printf("digite o codigo do bruxo:");
	scanf("%d", &novo.Codbruxo);
	printf("digite o codigo paciente: ");	
	scanf("%d", &novo.Codpaciente);
	printf("digite o codigo da pocao: ");
	scanf("%d", &novo.Codpocao);
	
	printf("quantos dias de tratamento: ");
	scanf("%d", &novo.dias);
	printf("quantas doses: ");
	scanf("%d", &novo.doses);
	return novo;	
}
 


void Menu_Bruxo(void)
{
	int imprimir = 1;
	int opcaoBruxo = 0;
	
	do
	{
		Imprimir_MenuSub(imprimir);
		scanf("%d", &opcaoBruxo);
		if(validacao_opcao(opcaoBruxo))
		{
			switch(opcaoBruxo)
			{
				case 1:
				{
					Listar(1);
					break;		
				}
				case 2:
				{
					 if(SalvarBruxo(infos_cadastro()) != 0)
					 {
					 	printf("salvo com sucesso!!\n");
					 }
					 else
					 {
					 	printf("Erro inesperado!\n");
					 }
					break;	
				}
				case 3:
				{
					Listar (1);	
					if(AtualizarBruxo( alterar_bruxo()) != 0)
					{
						printf("atualizado com sucesso!\n");
					}
					else
					{
						printf("erro na atualização!");
					}
					break;
				}
				case 4:
				{
					Listar(1);	
					int cod = codigo(1);
					
					for(int i = 0; i < QuantidadeTratamento(); i++)
					{
					 	Tratamento *buff = ObterTratamentoPeloIndice(i);
						
						if(cod == buff[i].Codbruxo)
						{
							printf("este bruxo está em tratamento!");
							break;
						}
				 		else if(ApagarBruxoPeloCodigo(cod) != 0)
				 		{
				 			printf("Apagado com sucesso!\n");
						}
						else
						{
							printf("Apagado com fracasso!\n");
						}
					}
				}
					
					
			}
		}
		else
		{
			printf("digite um numero valido!\n");
		}
		
	}while( opcaoBruxo != 0);

}











void Menu_Pocao(void)
{
	int imprimir = 3;
	int opcaoPocao = 0;
	
	do
	{
		Imprimir_MenuSub(imprimir);
		scanf("%d", &opcaoPocao);
		if(validacao_opcao(opcaoPocao))
		{
			switch(opcaoPocao)
			{
				case 1:
				{
					Listar(3);
					break;		
				}
				case 2:
				{
					 if(SalvarPocao(info_cadastroPocao()) != 0)
					 {
					 	printf("salvo com sucesso!!\n");
					 }
					 else
					 {
					 	printf("Erro inesperado!\n");
					 }
					break;	
				}
				case 3:
				{
					Listar (3);	
					if(AtualizarPocao( alterar_Pocao()) != 0)
					{
						printf("atualizado com sucesso!\n");
					}
					else
					{
						printf("erro na atualização!");
					}
					break;
				}
				case 4:
				{
					Listar(3);
					int cod = codigo(3);
					for(int i = 0; i < QuantidadeTratamento(); i++)
					{
					 	Tratamento *buff = ObterTratamentoPeloIndice(i);
						
						if(cod == buff[i].Codpocao)	
						{
							printf("este bruxo está em tratamento!");
							break;
						}
				 		else if(ApagarPocaoPeloCodigo(cod) != 0)
				 		{
				 			printf("Apagado com sucesso!\n");
						}
						else
						{
							printf("Erro ao apagar!\n");
						}
					}
						
				}
			}
		}
		else
		{
			printf("digite um numero valido!\n");
		}
		
	}while( opcaoPocao != 0);

}








void Menu_Paciente(void)
{
	int imprimir = 2;
	int opcaoPacientes = 0;
	
	do
	{
		Imprimir_MenuSub(imprimir);
		scanf("%d", &opcaoPacientes);
		if(validacao_opcao(opcaoPacientes))
		{
			switch(opcaoPacientes)
			{
				case 1:
				{
					Listar(2);
					break;		
				}
				case 2:
				{
					 if(SalvarPaciente(info_cadastroPaciente()) != 0)
					 {
					 	printf("salvo com sucesso!!\n");
					 }
					 else
					 {
					 	printf("Erro inesperado!\n");
					 }
					break;	
				}
				case 3:
				{
					Listar (2);	
					if(AtualizarPaciente( alterar_Paciente()) != 0)
					{
						printf("atualizado com sucesso!\n");
					}
					else 
					{
						printf("erro na atualização!");
					}
					break;
				}
				case 4:
				{
					Listar (2);	
					int cod = codigo(2);
					for(int i = 0; i < QuantidadeTratamento(); i++)
					{
						Tratamento *buff = ObterTratamentoPeloIndice(i);
						if(cod == buff[i].Codpaciente)
						{
							printf("este bruxo está em tratamento!");
							break;
						}
				 		else if(ApagarPacientePeloCodigo(cod) != 0)
				 		{
				 			printf("Apagado com sucesso!\n");
						}
						else
						{
							printf("Apagado com fracasso!\n");
						}
					}
				}	
			}
		}
		else
		{
			printf("digite um numero valido!\n");
		}	
	}while( opcaoPacientes != 0);

}





int Menu(void)
{
	int opcao = 0;
	
		
		Imprimir_Menu();
		scanf("%d", &opcao);	
		printf("------------------\n");
		return opcao;	
}
