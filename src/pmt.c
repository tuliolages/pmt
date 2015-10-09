#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* Flag set by ‘--help' or '-h’. */
static int help_flag;

/* Flag set by ‘--edit' or '-e’. */
static int edit_flag;
static int edit_value;

/* Flag set by ‘--pattern' or '-p’. */
static int pattern_flag;
// static char pattern_file[];

int main (int argc, char **argv)
{
  int c;

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"edit",    required_argument, 0, 'e'},
          {"pattern", required_argument, 0, 'p'},
          {"help",    no_argument,       0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "e:p:h",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'e':
          edit_flag = 1;
          // TODO tem que converter esse caray de optarg pra int
          printf ("option -e with value `%s'\n", optarg);
          break;

        case 'p':
          pattern_flag = 1;
          // TODO salvar string optarg
          printf ("option -p with value `%s'\n", optarg);
          break;

        case 'h':
          help_flag = 1;
          printf ("option -h\n");
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--help’, '--edit'
     or ‘--pattern’ as they are encountered,
     we report the final status resulting from them. */

  if (help_flag)
    puts ("help flag is set, stop everything else and print the help text!");

  printf("search mode: %s\n", edit_flag ? "approximated" : "exact (default)");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: \n");

      /* If pattern_flag is set, then the remaining arguments
         are target textfiles. Otherwise, the first one will be
         the pattern string*/
      if (!pattern_flag && optind < argc)
      {
         printf("pattern string: '%s'\n", argv[optind++]);
      }

      printf("target textfile expressions: ");
      while (optind < argc)
        // TODO usar fnmatch para auxiliar na lógica de encontrar os arquivos
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  exit (0);
}
