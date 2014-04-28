#define TAMANHO 50
#define NUMERO 512

/* Alunos : Leonardo Belinski
* Raffael Ciciliano Rossi
*
* O objetivo é propor uma estrutura de um buffer para banco de dados com funções básicas.
* A estrutura proposta possui falhas no momento que serão corrigidas ao longo do projeto
* e suas funções e operações também adequadas.
*
* Operações que são realizadas no momento:
* Criar struct e ler os metadados.
* Criar struct e ler os dados.
* Imprimir pagina e tupla especifica do buffer.
* */

typedef struct mm{
char name[TAMANHO]; //Nome do campo
char type;	//Tipo: char, int, double
int size;	//Tamanho do dado
char used;	//Bit para usado
int nreg;	//Numero de itens neste esquema
int tuplasize;	//Tamanho da tupla total
}schema;

typedef struct bbuffer{
char dados[NUMERO];	//Onde se encontram os dados
int tuplasize;	//Tamanho de cada tupla para acessos
int numTuplas;	//Contador de quantas tuplas compõem a página
int dirtybit;	//Dirty bit informa se algo foi alterado nas tuplas
int pincount;	//Controla se a tupla esta sendo usada
}pagina;

//Conversão de valores

unsigned int chartoint(char str[]);
schema * iniciameta(char linkmeta[], schema * meta);
pagina * iniciabuffer(char linkarquivo[], schema * meta, pagina * buffer);
int imprimetupla(pagina * buffer,schema * meta,int bufferpagina,int tupl);
