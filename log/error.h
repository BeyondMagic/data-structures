#define log_error(message)  \
  printf("\033[31m");       \
  puts(message);            \
  printf("\033[0m");        \
  exit(EXIT_FAILURE);
