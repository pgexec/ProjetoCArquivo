#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"



int main(int argc, char *argv[]) {

	int opcao = 0;
	
	if(InicializarBruxos() == 0)
	{
		printf("erro de alocação de memoria de bruxos!!");
		system("pause");
	}
	
	if(InicializarPocoes() == 0)
	{
		printf("erro de alocacao de memoria!!");
		system("pause");
	}
	
	if(InicializarPacientes() == 0)
	{
		printf("erro de alocacao de memoria!!");
		system("pause");
	}
	
	if(InicializarTratamento() == 0)
	{
		printf("erro de alocacao de memoria!!");
		system("pause");
	}
	
		
	do
	{
		opcao = Menu();	
	 	if(validacao_opcao(opcao) != 0)
		{
			switch(opcao)
			{
				case 1:
				{		
					Menu_Bruxo();
					break;
				}
				case 2:{
					Menu_Paciente();
					break;
				}
				case 3:{
					Menu_Pocao();
					break;
				}
				case 4:{
					Menu_tratamento();
					break;
				}
			}
		}
		else
		{
		printf("digite um numero valido!\n");	
		}

	
	
	}
	while(opcao != 0);
	printf("Obrigado por usar nosso sistema!\n");




	if( EncerraBruxos() != 0)
	{
		printf("Bruxos encerrado com sucesso!\n");
	}
	else
	{
		printf("erro ao encerrar");
	}
	
	if(EncerraPocoes() != 0)
	{
		printf("Pocoes encerrado com sucesso!\n");
	}
	
	if(EncerraPacientes() != 0)
	{
		printf("Pacientes encerrado com sucesso!\n");
	}
	if(EncerraTratamento() != 0)
	{
		printf("Tratamentos encerrado com sucesso!");
	}
	return 0;
}
