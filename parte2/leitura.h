#define tamanho 512
#define paginas 10

typedef struct {
 		char nome_campo[20];
 		char tipo_campo;
 		int tamanho_campo;
} campo;

struct pagina {
		unsigned char db;
		unsigned char cb;
		unsigned char num_reg;
		unsigned char nbyt;
		char data[tamanho];
};

typedef struct {
    char data[31];
    char meta[31];
}dic_dados;

void iniciaBuffer(struct pagina *bp);  // função que inicializa o buffer, setando os atributos da estrutura.

void copiaTupla(struct pagina *buffer,char *tupla, int pos); // função que copia a tupla(t) a partir da posição(pos) no buffer(bp).

void insereBuffer(struct pagina *bp, char *tuple); // função que procura pagina com registro disponivel para gravação da tupla(tuple) no buffer(bp).

void preencheTupla(char *tupla, char *dado, int inicio, int tam); // função que faz a copia do vetor de char(sc) para uma tupla(tg) a partir de uma posicao(st) até o comprimento(len) da mesma.

void imprimeTupla(struct pagina *bp, campo *c, int pag, int reg, int tamtupla, int num_campos); // função para impressao de um registro de uma pagina

void formaTupla(char *tp, const void *v, char t, int st, int tam); // função que recebe os dados extraidos da leitura do arquivo(*v), tratado conforme o tipo(t) e encaminhado para ser "anexado" à tupla

void lerMeta(char *name, campo *c, int num_campos); // função que faz a leitura dos metadados a partir de um arquivo(name) e grava estes na variavel tipo campo(c). Variavel num_campos representa a quantidade de campos seguidos referentes a um registro.

void lerData(char *name, struct pagina *bp, campo *c, int num_campos); // função que faz a leitura dos dados a partir do arquivo(name) que serão armazenados em tuplas que serão gravadas no buffer. Variavel c possui os metadados e variavel num_campos a quantia de campos de uma tupla.

int buscaCampos(char *name); // função que extrai o numero de campos por tupla a partir do arquivo(name).

dic_dados *criaArqDicionario(char *name1, char *arqMeta, char *arqData);

dic_dados *selecionArqDicionario(char *nomeArqDic);
