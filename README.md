BufferManager
=============

Trabalho Buffer Manager
Banco de Dados II
Autores:	Leonardo Belinski
		Raffael Ciciliano Rossi

----------------------------------------------------

Arquivos:

	Faz parte do pacote de arquivos para o trabalho os seguintes arquivos:

- biblioteca.h				//contém a declaração da estrutura do buffer e do esquema e o protótipo das funções usadas
- biblioteca.c				//contém as funções do programa
- arquivo.c				//exemplo de main para o programa

----------------------------------------------------

Para compilar:

	Para compilar os arquivos e linka-los será necessário realizar três instruções de compilação. Primeiramente, compila-se o arquivo biblioteca.c, com a instrução

					gcc -c -g biblioteca.c

em seguida, o arquivo da main será compilado com a seguinte instrução

					gcc -c -g arquivo.c

para linka-los será necessário realizar a terceira instrução

				gcc -o nome_qualquer arquivo.o biblioteca.o

e para o programa ser executado, basta que seja digitado

	./nome_qualquer_compilação_anterior diretório_arquivo_meta diretório_arquivo_dados

sendo a ordem dos arquivos e sua respectiva localização importante para o funcionamento do programa.


Funcionamento:

	Após compilado, o programa recebe junto com sua chamada dois argumentos, sendo o primeiro para indicar o nome/diretório do arquivo de meta-dados e o segundo para indicar o nome/diretório do arquivo de dados, sendo essa ordem essencial para o funcionamento do programa.

	A primeira ação do programa e identificar o esquema de meta-dados, encarregado pela função iniciameta, que devolve uma estrutura com as características do conteúdo do arquivo de dados.

	A segunda ação do programa é ler o arquivo de dados, baseando-se na estrutura de meta-dados que foi lido anteriormente na função iniciameta.



Funções:

unsigned int chartoint(char str[])

	Converte uma string passada para um valor int, através de deslocamentos de bit na string.

schema * iniciameta(char linkmeta[], schema * meta)

	Transforma a leitura do arquivo de meta-dados em informação para a estrutura meta do programa.

Devolve o arquivo de meta-dados na memória.
Paramêtro 1: nome/diretório do arquivo que contém as informações do meta, que é passado quando o programa é executado
Paramêtro 2: um ponteiro do tipo da estrutura schema.

O programa executa a leitura da quantidade de dados que serão lidos no arquivo de meta-dados e aloca um vetor que receberá a característica de cada informação que será lida no arquivo de dados, sendo estas: nome, tamanho e tipo. A cada passado pelo arquivo, já é somada a quantidade de bytes que serão usados por cada tupla, e armazenado na estrutura meta, no campo tuplasize, para controle futuro da informação.

pagina * iniciabuffer(char linkarquivo[], schema * meta, pagina * buffer)

	A partir da leitura do meta com a função iniciameta, essa função irá ler o arquivo de dados e segundo o esquema fornecido no arquivo de meta-dados, será realizada a leitura do arquivo de dados e a informação será copiada para o buffer.

Devolve o conteúdo do arquivo de dados na memória conforme estrutura do meta.
Paramêtro 1: ponteiro do tipo schema que contém o meta
Paramêtro 2: ponteiro do tipo buffer, onde será armazenado os dados lidos

	O primeiro passo é verificado se o arquivo de dados passado contém algo e se existe, se existir e conter algo o programa vai em frente, caso contrário fecha o arquivo.
	Logo após, será alocada a estrutura do buffer, que é do tamanho de uma estrutura buffer multiplicada pela constante TAMANHO, que define o número máximo de páginas do buffer.
	No while seguinte a alocação, são extraídos os dados do arquivo conforme cada informação é identificada pelos if's em sequência.

int imprimetupla(pagina * buffer,schema * meta,int bufferpagina,int tupl)

	Essa função mostra ao usuário o conteúdo de uma tupla contida no buffer.

Devolve um valor inteiro que respectivamente representa algo para o programa.
Valores: 0 – se não houve erro, 1 – se houve algum erro durante a impressão, alguma informação não conseguiu ser impressa, -1 erro que nunca será alcançado, -2 caso a página não está sendo usada ou não foi alocada e -3 caso a tupla não exista naquela página.

	Será testado se aquela página solicitada está em uso, ou seja, existe alguma informação nela, se existir, será verificado se aquela tupla possa estar naquela página, caso seja sim, o programa continua em frente, se não será retornado um valor identificando isso. Logo, será copiada a tupla respectiva que contém a informação solicitada, e logo depois passará pelo processo de identificar a informação copiada conforme seu tipo, e imprimir ela na tela.






