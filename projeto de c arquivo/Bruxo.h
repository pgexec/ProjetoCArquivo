#define TAM_STRING 20

typedef struct {
	int codigo;
	char nome[TAM_STRING];
	char especialidade[TAM_STRING];
} Bruxo;

int quantidade_bruxo_ini();
int InicializarBruxos();
int EncerraBruxos();
int SalvarBruxo(Bruxo b);
int QuantidadeBruxos();
Bruxo* ObterBruxoPeloIndice(int indice);
Bruxo* ObterBruxoPeloCodigo(int codigo);
int AtualizarBruxo(Bruxo b);
int ApagarBruxoPeloCodigo(int codigo);
int ApagarBruxoPeloNome(char* nome);
