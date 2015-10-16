#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct program_args {
  int allowed_edit_distance;
  char* pattern_file;
  char** patterns;
  bool help_flag;
  char** source_text_files;

  program_args()
    : allowed_edit_distance(0),
      pattern_file(0),
      patterns(0),
      help_flag(false),
      source_text_files(0) { }
} program_args;

program_args get_program_parameters(int argc, char** argv) {
  int option_index;
  int current_parameter;
  int edit_distance = 0;
  char* pattern_file = 0;
  program_args args;

  struct option long_options[] =
    {
      {"edit",    required_argument, 0, 'e'},
      {"pattern", required_argument, 0, 'p'},
      {"help",    no_argument,       0, 'h'},
      {0, 0, 0, 0}
    };

  while (1) {
    current_parameter = getopt_long(argc, argv, "e:p:h", long_options, &option_index);

    if (current_parameter == -1) {
      break;
    }

    switch (current_parameter) {
      case 0:
        // No momento, nenhum argumento está sendo usado para setar uma flag
        break;
      case 'e':
        args.allowed_edit_distance = atoi(optarg);
        break;
      case 'p':
        args.pattern_file = optarg;
        break;
      case 'h':
        args.help_flag = true;
        break;
      case '?':
        // Um argumento desconhecido é apenas ignorado no momento
        break;
      default:
        abort();
    }
  }

  if (optind < argc) {
    /* If pattern_flag is set, then the remaining arguments
       are target textfiles. Otherwise, the first one will be
       the pattern string*/
    if (!args.pattern_file) {
      args.patterns = new char*[2];
      args.patterns[0] = argv[optind++];
      args.patterns[1] = 0;
    }

    if (optind < argc) {
      int source_text_files_length = argc - optind + 2;
      int i = 0;

      args.source_text_files = new char*[source_text_files_length];

      while (optind < argc) {
        args.source_text_files[i++] = argv[optind++];
      }

      args.source_text_files[i] = 0;
    }
  }

  return args;
}

void print_help_text() {
  cout << "Usage: pmt [options] [pattern] <textfilepath> [moretextfiles]" << endl;
  cout << "Options:" << endl;
  cout << "  -e <edit distance>\t\tSets allowed edit distance for approximated text search" << endl;
  cout << "  --edit=<edit distance>\tSame as previous option" << endl;
  cout << "  -p <pattern file>\t\tSpecifies file from which the program should read the patterns to be used (each line of the file specifies a pattern)" << endl;
  cout << "  --pattern=<pattern file>\tSame as previous option" << endl;
  cout << "  -h\t\t\t\tShows this message" << endl;
  cout << "  --help\t\t\tSame as previous option" << endl;
  cout << endl << "  If a pattern file is not specified, the first argument given to pmt will be read as the only pattern to be searched for in the text file. Several source text files can be specified at the same time." << endl;
}

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
        cout << "Nenhum padrão foi fornecido." << endl;
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
  }

  exit (0);
}
