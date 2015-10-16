struct program_args {
  int allowed_edit_distance;
  char* pattern_file;
  char** patterns;
  bool help_flag;
  char** source_text_files;
  program_args();
};

program_args get_program_parameters(int argc, char** argv);
void print_help_text();
int glob_error(const char *path, int eerrno);
char** match_files(int files_index, char **source_text_files);
