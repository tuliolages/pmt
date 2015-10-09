Primeiro projeto da cadeira de PCC.

TODO:
	-makefile
	-getopt para ler os argumentos (http://www.gnu.org/software/libc/manual/html_node/Getopt.html#Getopt) [doing]
	-fnmatch para percorrer os arquivos alvo
	-algoritmos de busca exata e aproximada
	-separar em .c e .h
	-fazer doc de --help

Por enquanto, para rodar:
	-cd até src
	-gcc -o pmt pmt.c -I .

Aí dá para rodar comandos como tem na especificação do projeto, ex: ./pmt "oi" arq1 arq2