#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioteca.h"

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

//Conversão de valores

unsigned int chartoint(char str[]){
    int i0=0,i1=0,i2=0,i3=0;
    i0=str[0];
    i1=str[1];
    i2=str[2];
    i3=str[3];
    int numero=(i3>>=24) | (i2>>=16) | (i1>>=8) | i0;
    return numero;
}

schema * iniciameta(char linkmeta[], schema * meta){
    char ch,copia;
    int c,d,e,f,g,nregistro=0,tuplasize=0,ntuplas=0,teste=0,ret=0;	//c,d,e,f,g são contadores .
    FILE *metadados,*dados;
    metadados = fopen(linkmeta, "r");	//Abre arquivo de meta dados para leitura

    if(metadados == NULL)
        return meta;
    else{
        if(feof(metadados)==0){
            fread(&nregistro,sizeof(int),1,metadados);
        }
        ch=1;
        meta=(schema *)malloc(sizeof(schema)*nregistro);
        for(c=0;c<nregistro;c++){
            meta[c].used=1;	//Seta esta pagina de schema para usada
            //Lê a estrutura dos dados
            meta[c].nreg=nregistro;
            for(d=0;ch!=0;d++){ //concatena string para estrutura
                fread(&ch,sizeof(char),1,metadados);
                meta[c].name[d]=ch;
            }
            ch=1;	//sting criada e ch !=0 para possivel interação futura
            fread(&meta[c].type,sizeof(char),1,metadados);	//Leitura do tipo
            fread(&meta[c].size,sizeof(int),1,metadados);	//Leitura do tamanho do dado
            tuplasize=tuplasize+meta[c].size;
        }
    }
    meta[0].tuplasize=tuplasize;
    fclose(metadados);
    return meta;
}

pagina * iniciabuffer(char linkarquivo[], schema * meta, pagina * buffer){
    char ch,*copia;
    int c,d,e,f,g,h,ntuplas=0,teste=0,ret=0,readint=0;	//c,d,e,f,g,h são contadores .
    double readouble=0.0;
    FILE *dados;

    //Lendo arquivo de dados e colocando no bufferpool

    dados = fopen(linkarquivo,"r");
    if(dados == NULL)
        return buffer;
    else{
        buffer=(pagina *)malloc(sizeof(pagina)*TAMANHO);
        for(c=0;c<TAMANHO;c++){	//Navega pelas paginas
            buffer[c].tuplasize=meta[0].tuplasize;
            buffer[c].numTuplas=0;
            buffer[c].pincount=0;
            e=meta[0].tuplasize;
            h=0;	//Numero de tuplas na pagina
            while(e<NUMERO){	//Incrementa pelo tamanho da tupĺa para caber na página
                buffer[0].pincount=1;
                d=meta[0].tuplasize*h;
                while(d<meta[0].tuplasize*(h+1)){

                    for(f=0;f<meta[0].nreg;f++){
                        if(meta[f].type=='s' || meta[f].type=='S'){	//Leitura de string
                            copia=(char*)malloc(sizeof(char)*meta[f].size);
                            teste=fread(copia,meta[f].size,1,dados);
                            if(teste>=1){	//Verifica se a leitura foi valida
                                for(g=0;g<meta[f].size;g++,d++){
                                    buffer[c].dados[d]=copia[g];
                                }
                            }else{
                                fclose(dados);
                                return buffer;
                            }
                        }else if(meta[f].type=='i' || meta[f].type=='I'){
                            teste=fread(&readint,meta[f].size,1,dados);
                            if(teste>=1){
                                buffer[c].dados[d]=(char)readint << 0;
                                d++;
                                buffer[c].dados[d]=(char)readint << 8;
                                d++;
                                buffer[c].dados[d]=(char)readint << 16;
                                d++;
                                buffer[c].dados[d]=(char)readint << 24;
                                d++;
                            }else{
                                fclose(dados);
                                return buffer;
                            }
                        }else if(meta[f].type=='d' || meta[f].type=='D'){
                            readouble=0.0;
                            teste=fread(&readouble,meta[f].size,1,dados);
                            if(teste>=1){
                                char * aponta=(char *)&readouble;
                                for(g=0;g<meta[f].size;g++,d++){
                                    buffer[c].dados[d]=aponta[g];
                                }
                            }else{
                                fclose(dados);
                                return buffer;
                            }
                        }else{
                            buffer[0].pincount=1;
                            fclose(dados);
                            return buffer;
                        }

                    }
                }
                buffer[c].pincount=1;
                buffer[c].numTuplas=buffer[c].numTuplas+1;
                h++;
                e=e+meta[0].tuplasize;
            }
        }
    }
    buffer[0].pincount=1;
    fclose(dados);
    return buffer;
}

int imprimetupla(pagina * buffer,schema * meta,int bufferpagina,int tupl){

    if(buffer[bufferpagina].pincount>0){	//Se a pagina esta no buffer
        if(buffer[bufferpagina].numTuplas>=tupl){	//Se a tupla esta na pagina
            char copia[buffer[bufferpagina].tuplasize];
            int c=0,d=0,e=0;	//e é o contador da tupla local
            for(c=0,d=buffer[bufferpagina].tuplasize*tupl;c<buffer[bufferpagina].tuplasize;c++,d++){
                copia[c]=buffer[bufferpagina].dados[d];	//Copia tupla a ser impressa para uma local
            }
            for(c=0;c<meta[c].nreg;c++){
                if(meta[c].type=='S' || meta[c].type=='s'){	//Imprime string
                    char imprime[meta[c].size];
                    for(d=0;d<meta[c].size;d++,e++){
                        imprime[d]=copia[e];
                    }
                    printf("\n %s \t %s \t",meta[c].name,imprime);
                }else if(meta[c].type=='I' || meta[c].type=='i'){
                    char imprime[meta[c].size];
                    for(d=0;d<meta[c].size;d++,e++){
                        imprime[d]=copia[e];
                    }
                    int imp=chartoint(imprime);
                    printf("\n %s\t %d ",meta[c].name,imp);
                }else if(meta[c].type=='D' || meta[c].type=='d'){
                    char imprime[meta[c].size];
                    for(d=0;d<meta[c].size;d++,e++){
                        imprime[d]=copia[e];
                    }

                    double imp;
                    memcpy(&imp,imprime, sizeof(double));
                    printf("\n %s \t %lf \t",meta[c].name,imp);
                }else{
                    return 1;
                }
            }
            return 0;
        }else{
            return -3;
        }
    }else{
        return -2;
    }
    return -1;
}
