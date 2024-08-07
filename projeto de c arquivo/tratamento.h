


typedef struct{
	int codigo;
	int Codbruxo;
	int Codpocao;
	int Codpaciente;
	int dias;
	int doses;
	
}Tratamento;

int quantidade_tratamentos_ini();
Tratamento* ObterTratamentoPeloIndice(int indice);	
int EncerraTratamento(void);
int InicializarTratamento(void);
int QuantidadeTratamento(void);
int SalvarTratamento(Tratamento novo);
int AtualizarTratamento(Tratamento novo);
Tratamento* ObterTratamentoPacienteCodigo(int codPaciente, int* qtd);
Tratamento* ObterTratamentoBruxoCodigo(int codBruxo, int* qtd);
int ApagarTratamentosPeloCodigo(int codigo);

