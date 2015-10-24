struct program_args {
  program_args();
  ~program_args();

  int allowed_edit_distance;
  char* pattern_file;
  char** patterns;
  bool help_flag;
  char** source_text_files;
};

program_args get_program_parameters(int argc, char** argv);
void print_help_text();
int glob_error(const char *path, int eerrno);
void search_files(program_args args);
int is_regular_file(const char *path);
