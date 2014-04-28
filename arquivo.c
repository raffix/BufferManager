#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioteca.h"

int main(){
schema * meta;
pagina * buffer;

meta=iniciameta("file/meta.dat",meta);
buffer=iniciabuffer("file/data.dat",meta,buffer);
int a;
a=imprimetupla(buffer,meta,0,2);
printf("\n ");
return 0;
}
