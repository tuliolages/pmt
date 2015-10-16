#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <iostream>

#include "utils.h"
#include "input/FileReader.h"

using namespace std;

int main (int argc, char **argv) {
  program_args args = get_program_parameters(argc, argv);

  if (args.help_flag) {
    print_help_text();
  } else {
    cout << "Modo de busca: ";

    if (args.allowed_edit_distance > 0) {
      cout << "aproximada (distancia máxima = " << args.allowed_edit_distance << ")" << endl;
    } else {
      cout << "exata" << endl;
    }

    if (args.pattern_file) {
      cout << "Arquivo de padrões: " << args.pattern_file << endl;
    } else {
      cout << "Nenhum arquivo de padrões foi fornecido." << endl;

      if (!args.patterns) {
        cerr << "Nenhum padrão foi fornecido." << endl;
        exit(1);
      } else {
        cout << "Padrões fornecidos:" << endl;
        for (int i = 0; args.patterns[i]; i++) {
          cout << "  " << args.patterns[i] << endl;
        }
      }
    }

    if (args.source_text_files) {
      cout << "Arquivos de texto a serem buscados:" << endl;
      for (int i = 0; args.source_text_files[i]; i++) {
        cout << "  " << args.source_text_files[i] << endl;
      }
    }

    exit (0);
  }
}
