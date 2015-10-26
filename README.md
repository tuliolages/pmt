# Projeto 1 - Processamento de Cadeias de Caracteres

(Este arquivo está escrito em [Markdown](https://daringfireball.net/projects/markdown/syntax#link). Para lê-lo em toda sua glória, abra o [repósitório do projeto no Github](https://github.com/tuliolages/pmt) ou passe esse texto por algum pré-processador)

## Integrantes:
- Daniel de Jesus Oliveira (djo)
- Rafael Nunes Galdino da Silveira (rngs)
- Túlio Paulo Lages da Silva (tpls)

## Instruções de compilação
Para compilar o projeto, basta executar o comando `make` ou `make pmt`, e para executá-lo, rodar o executável `pmt` que será gerado no diretório `bin`. Para mais informações sobre o uso do programa, a opção `--help` está disponível. Além disso, é possível executar o programa através do comando `make run args="<argumentos>"`, onde *argumentos* são os mesmos argumentos da execução normal do `pmt`, entre aspas.

## Instruções de execução
Exemplo de uso: pmt [opções] [padrão] arquivo_de_entrada [outros_arquivos_de_entrada ...]" << endl;

Opções:


-e, --edit=< edit distance> - Configura a distância máxima de edição;

-p, --pattern=< pattern file> - Especifica o arquivo de onde serão lidos os padrões a serem buscados (um por linha);

-h, --help - Mostra uma versão em inglês destas instruções.

-k, --kmp - Hablitia a utilização do Knuth-Morris-Pratt (KMP) como algoritmo para casamento exato de padrão.

-q, --quiet - Habilita a opção `quiet` e o algoritmo não imprimirá as saídas (útil para análise de tempo).

Se um arquivo com padrões não for especificado, o primeiro argumento após as opções dado ao `pmt` será interpretado como o único padrão a ser buscado. Vários arquivos de entrada podem ser especificados.

## Opções de algoritmos

O pmt implementado pelo grupo inclui a implementação dos algoritmos Knuth-Morris-Pratt (KMP),  Boyer-Moore (BM) e Aho-Corasick (AC) para casamento exato de padrões, e Sellers para casamento aproximado. De acordo com os parâmetros fornecidos na execução da aplicação, o algoritmo é escolhido:

- Se for especificada uma distância máxima de edição maior que zero, o algoritmo Sellers é escolhido;
- Caso contrário, se mais de um padrão for especificado, o algoritmo AC é escolhido;
- Caso contrário, se a opção -k estiver habilitada o algoritmo KMP é escolhido;
- Caso contrário, o algoritmo BM é escolhido.
