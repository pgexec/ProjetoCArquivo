
#include "Bruxo.h"
#include "Pocao.h"
#include "Paciente.h"
#include "tratamento.h"

int Menu(void);
int validacao_opcao(int opcao);
void Imprimir_Menu(void);
void Imprimir_MenuSub(int opcaoMenu);
void Listar (int opcao);
int codigo(int codigo);


void Menu_Bruxo(void);
Bruxo infos_cadastro(void);
Bruxo alterar_bruxo(void);
int verifica_BruxoExiste(int codigo);
int verificador_bruxo(int codigo);




void Menu_Pocao(void);
Pocao alterar_Pocao(void);
Pocao info_cadastroPocao(void);
int verificador_pocao(int codigo);
int verifica_PocaoExiste(int codigo);

void Menu_Paciente(void);
Paciente info_cadastroPaciente(void);
Paciente alterar_Paciente(void);
int verifica_PacienteExiste(int codigo);
int verificador_paciente(int codigo);



int verificador_CodigoTratamento(int codigo);
void Menu_tratamento(void);
Tratamento infos_tratamento(void);
int Listar_TratamentosPaciente(void);
int Listar_TratamentoBruxo(void);
int validacao_opcaoTratamento(int opcao);
