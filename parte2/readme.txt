Alunos: Caciano, Mateus, Thiago. Modificações : Leonardo e Raffael.

Descrição do programa:

O programa inicia definindo a estrutura dos dados a partir das informações extraídas da leitura do arquivo de metadados. 
São extraído todos os campos (incluíndo nome, tipo e tamanho do campo) que vão compor cada tupla. 
A partir desta leitura já é determinado o tamanho que cada tupla terá, além do tamanho de cada campo, possibilitando a leitura de todos os registros(tuplas) do arquivo de dados.

Em seguida, definida a estrutura dos dados, é feita a leitura dos dados do arquivo contendo os dados(função lerDados()). Cada campo é lido baseado no tamanho dele(definido na estrutura).
Baseado na quantidade de campos que será composto cada registro, os campos são extraídos e assim os mesmos são anexados e organizados em tuplas. 
Quando uma tupla está completa(feita a leitura e anexados o total de campos em sequencia que formam um registro), a mesma é enviada para a função insereBuffer() 
que busca uma página com espaço livre no Buffer e copia a tupla caracter por caracter para a página do buffer.

Cada página tem capacidade de 512 bytes (variável tamanho e o buffer possui 10 páginas
(variável paginas). A alteração da capacidade de uma página e da quantidade de páginas no buffer é possível a partir da alteração das variáveis tamanho e paginas respectivamente 
localizadas no arquivo leitura.h. Ambas estão no início do arquivo declaradas como variáveis globais.


Arquivo main: Para mostrar o funcionamento, foi criado o arquivo main.c que recebe por parâmetro os arquivos de metadados e dados respectivamente. Dentro do escopo da main, 
é criada uma variável do tipo int para armazenar a quantidade de campos que cada tupla vai conter (int num_campos), recebendo o valor através do retorno da função buscaCampos().
Na sequencia, é criada a estrutura bufpool que é nosso Buffer. Para ele é alocado um espaço para x páginas. Esse valor de páginas é definido pela variável paginas(já comentado 
seu funcionamento no parágrafo acima). Depois disso é criada a estrutura que irá armazenar como estão estruturados os dados no arquivo de dados. 
Essas informações estão no arquivo de metadados. A estrutura que irá armazenar isto é definida como do tipo campo e terá seu tamanho(tamanho do vetor) definido pela variável num_campos.
Em seguida é necessário iniciar o buffer(função iniciaBuffer()) e ler os arquivos meta.dat e data.dat através das funções lerMeta() e lerData() respectivamente. 
Por fim, é feita a impressão de uma tupla de uma página do buffer através da função imprimeTupla().


Modificações :
O programa foi modificado para receber como entrada o nome do dicionário de dados, este dicionário contém o nome dos arquivos com metadados e dados. Com isso apenas um item é necessário ser passado como parametro. As funções adicionadas apenas alteram o programa para funcionar com dicionário e não direto com os nomes dos arquivos. Como entrada o programa deve receber o nome do arquivo de dicionário, este sera aberto e lá deve conter o nome do arquivo com metadados da tabela e o nome do arquivo que contém os dados arquivo referido, ambos os nomes possuem 30 bytes de tamanho. Para melhor compreensão e funcionamento do código foi acrescentada uma função que cria o arquivo do dicionário, esta recebe 3 strings as quais são : nome do arquivo de dicionário, nome do arquivo de metadados e nome do arquivo de dados, com isso ele cria no diretório corrente os arquivos. Em nenhum momento existe limitação quanto a composição dos nomes, apenas seu tamanho. O grupo optou por esta abordagem para maior flexibilidade, as limitação podem ser aplicadas camadas acima das funções chamadas. 

Na main que tem como exemplo é o caso onde é criado o arquivo do dicionário, portanto o arquivo não existe, o mesmo deve ser criado para os arquivos de meta e dados existentes.