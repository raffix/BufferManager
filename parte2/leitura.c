#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

int tamtupla = 0; // variavel que vai indicar o tamanho das tuplas
int num_reg;

// função para inializar zerando todos os controles das paginas
void iniciaBuffer(struct pagina *buffer) {
	int i;
	for (i=0;i<paginas;i++)
	{
		buffer[i].db=0;
		buffer[i].cb=0;
		buffer[i].num_reg=0;
		buffer[i].nbyt=0; // tamanho da tupla
	}
}

void copiaTupla(struct pagina *buffer,char *tupla, int pos) {
	int i, j;
	for(i = pos, j=0; i< pos+tamtupla; i++, j++) {
		buffer->data[i] = tupla[j];
	}
}

void insereBuffer(struct pagina *buffer, char *tuple) {
	int i;
	for(i=0; i<paginas; i++) {
		if(buffer[i].num_reg < num_reg) { // enquanto tiver espaço na página
			copiaTupla(&buffer[i],tuple,(buffer[i].num_reg * tamtupla));
			buffer[i].num_reg++;
			return;
		}
	}
	printf("\nERROR - Page Not Found!"); // caso nao encontra pagina disponível emite mensagem de erro
}

union c_double
{
	double dbl;
	char   cdbl[sizeof(double)];
};

union c_int
{
	int  num;
	char cint[sizeof(int)];
};

union c_float
{
	float  flt;
	char cflt[sizeof(float)];
};

void preencheTupla(char *tupla, char *dado, int inicio, int tam) {
	int i,j = 0;
	for (i=inicio;i<(inicio+tam);i++,j++)
	  tupla[i]=dado[j];
}


void imprimeTupla(struct pagina *buffer, campo *c, int pag, int reg, int tamtupla, int num_campos) {
	printf("\n");
	int i =0,j=0, pos=0;
	if (paginas<pag) printf("\nERRO - Pagina não existente, Buffer com apenas %d paginas\n", paginas);
	else if(buffer[pag].num_reg < reg) printf("\nERRO - Registro não existente\n");
	else {
		pos = (reg-1)*tamtupla;
		for(i = 0; i < num_campos; i++){
			j=pos;
			if (c[i].tipo_campo == 'S') {
				printf("\n%s:\t", c[i].nome_campo);
				while(buffer[pag].data[j] != '\0') {
					printf("%c", buffer[pag].data[j++]);
				}
				pos+=c[i].tamanho_campo;
			}

			if (c[i].tipo_campo == 'I') {
				printf("\n%s:\t", c[i].nome_campo);
				int *tpInt=(int *)&buffer[pag].data[pos];
				printf("%d ",*tpInt);
				pos+=4;
			}
			if (c[i].tipo_campo == 'D') {
				printf("\n%s:\t", c[i].nome_campo);
				double *tpDouble=(double *)&buffer[pag].data[pos];
				printf("%.2f ",*tpDouble);
				pos+=8;
			}
		}
	}
}

// função para formaçao da tupla a partir dos dados extraidos do disco
void formaTupla(char *tupla, const void *dado, char tipo, int tamAtual, int tamDado)
{
	char  *str=(char *)dado;
	int *i=(int *)dado;
	double *d=(double *)dado;
	float *f=(float *)dado;
	union c_double cd;
	union c_float cf;
	union c_int ci;
	ci.num=*i;
	cd.dbl=*d;
	cf.flt=*f;
	switch (tipo)
	{
	  case 'S': preencheTupla(tupla,str,tamAtual,tamDado);
	            break;
	  case 'I': preencheTupla(tupla,ci.cint,tamAtual,4);
	            break;
	  case 'D': preencheTupla(tupla,cd.cdbl,tamAtual,8);
	            break;
	  case 'F': preencheTupla(tupla,cf.cflt,tamAtual,4);
				break;
	}
}

void lerMeta(char *name, campo *c, int num_campos) { // função responsável por extrair os metadados, armazendo os dados na variável do tipo campo passada à funcao como parametro
	int i, j;
	FILE *fp;
	fp = fopen(name,"r");
	char caractere;
	fseek(fp,4,0);
	for(i = 0; i < num_campos; i++){
		j=0;
		do
		{
			fread(&caractere, sizeof(char),1, fp);
			c[i].nome_campo[j] = caractere;
			j++;
		}while(caractere != '\0');
		fread(&c[i].tipo_campo, sizeof(char), 1, fp);
		fread(&c[i].tamanho_campo, sizeof(int), 1, fp);
		tamtupla += c[i].tamanho_campo;
		printf("\t%s",c[i].nome_campo);
		printf("\t%c",c[i].tipo_campo);
		printf("\t%d\n",c[i].tamanho_campo);
	}
	num_reg = (int)(tamanho/tamtupla); // calcula o numero de registros que uma página poderá conter.
	fclose(fp);
	return;
}

//cria arquivo dicionario
dic_dados *criaArqDicionario(char *name1, char *arqMeta, char *arqData) { // função responsável por extrair os metadados, armazendo os dados na variável do tipo campo passada à funcao como parametro
    FILE *fp;
    dic_dados *dicio_dados = (dic_dados *)malloc(sizeof(dic_dados));
    fp = fopen(name1,"w");
    strcpy(dicio_dados->meta,arqMeta);                              //copiando conteudo(nome arquivo meta)
    strcpy(dicio_dados->data,arqData);                              //copiando conteudo(nome arquivo data)
    fwrite(dicio_dados->meta,sizeof(dicio_dados->meta),1,fp);
    fwrite(dicio_dados->data,sizeof(dicio_dados->data),1,fp);
    fclose(fp);
    return dicio_dados;
}

dic_dados *selecionArqDicionario(char *nomeArqDic) { // função responsável por extrair os metadados, armazendo os dados na variável do tipo campo passada à funcao como parametro

    FILE *fp;
    dic_dados *dicio_dados = (dic_dados *)malloc(sizeof(dic_dados));

    fp = fopen(nomeArqDic,"r");
    if(!fp){
        return NULL;
    }
    else{
        fread(&dicio_dados->meta,sizeof(char),31,fp);
        fread(&dicio_dados->data,sizeof(char),30,fp);
        fclose(fp);
        return dicio_dados;
    }
}


void lerData(char *name, struct pagina *bp, campo *c, int num_campos) {
	char nometeste[tamtupla];
	double dteste;
	int iteste, i;
	int tamanho_atual;
	char *tuple=(char *)malloc(sizeof(char)*tamtupla);
	FILE *fp;
	fp = fopen(name,"r");
	if(!fp){
		printf( "Erro na abertura do arquivo");
    	return;
	}
	while (!feof(fp)) {
		tamanho_atual = 0;
		for(i = 0; i < num_campos; i++){
			if(c[i].tipo_campo == 'S'){
				fread(&nometeste, sizeof(char)*c[i].tamanho_campo,1, fp);
				formaTupla(tuple,(void *)nometeste,'S',tamanho_atual, c[i].tamanho_campo);
			}
			if(c[i].tipo_campo == 'D'){
				fread(&dteste, sizeof(double),1, fp);
				formaTupla(tuple,(void *)&dteste,'D',tamanho_atual,0);
			}
			if(c[i].tipo_campo == 'I'){
				fread(&iteste, sizeof(int),1, fp);
				formaTupla(tuple,(void *)&iteste,'I',tamanho_atual,0);
			}
			tamanho_atual+=c[i].tamanho_campo;
		}
		insereBuffer(bp, tuple);
	}
	fclose(fp);
	return;
}

int buscaCampos(char *name) { // recebe arquivo como parametro e retorna o total de campos de cada registro
	int campos=0;
	FILE *fp;
	fp = fopen(name,"r");
	if(!fp){
		printf( "Erro na abertura do arquivo");
    	return 0;
	}
	fread(&campos, sizeof(int),1, fp);
	fclose(fp);
	return campos;
}

