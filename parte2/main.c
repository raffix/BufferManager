#include<stdio.h>
#include<stdlib.h>
#include "leitura.h"
int main(int argc,char *argv[]){
    int tamtupla, sucessoLeitura;
    dic_dados *dicio_dados;
	printf("\nEstrutura do meta.dat:\n");
	//deve ser passado um nome com 30 caracteres para cada arguemento de entrada, 32, 30
    dicio_dados = selecionArqDicionario(argv[1]);
    if(dicio_dados == NULL)
        dicio_dados = criaArqDicionario(argv[1], argv[2], argv[3]);         //nome tabela, nome meta, nome data
	int num_campos = buscaCampos(dicio_dados->meta); // recebe quantos campos terá cada tupla*/
	struct pagina *bufpool;
	bufpool=(struct pagina *)malloc(sizeof(struct pagina)*paginas);
	campo c[num_campos];
	iniciaBuffer(bufpool);
	lerMeta(dicio_dados->meta,&*c,num_campos); // chamada de função para ler arquivo contendo os metadados (usando o nome do arquivo, o endereço da variavel campo que recebe os parametros e o total de campos todos como parametro)
	lerData(dicio_dados->data,bufpool,c, num_campos); // chamada de função para ler arquivo contendo os dados usando o nome do arquivo, a variavel contendo os metadados e o total de campos como parametro.
	printf("\nImpressão de um registro de uma página:");

	//      numero da pagina  numero do registro
	//                     |  |
	imprimeTupla(bufpool, c, 0, 1, tamtupla, num_campos);
	return 0;
}
