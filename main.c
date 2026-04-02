#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WHITE_SPACE " "

int main(int argc, char **argv) {
  int new_line_flag = 1;
  int e_flag = 0;
  int arg_index = 1;

  // flags
  // string end in c lang is \0
  while (arg_index < argc && argv[arg_index][0] == '-' &&
         argv[arg_index][1] == '\0') {
    char *pointer_to_flag_argument = argv[arg_index] + 1;
    int valid_flag = 1;

    while (*pointer_to_flag_argument && valid_flag) {
      switch (*pointer_to_flag_argument) {
      case 'n':
        new_line_flag = 0;
        break;
      case 'e':
        e_flag = 1;
        break;
      case 'E':
        e_flag = 0;
        break;
      default:
        valid_flag = 0;
        break;
      }

      pointer_to_flag_argument++;
    }

    if (!valid_flag) {
      break;
    }

    pointer_to_flag_argument++; // next flag argument
  }

  for (arg_index = 1; arg_index < argc; arg_index++) {
    // const void *buf
    ssize_t written = write(STDOUT_FILENO, argv[arg_index],
                            strlen(argv[arg_index])); // syscall -> kernel
    if (written == -1) {
      return EXIT_FAILURE;
    }

    // todo: move to funcatin is_last_arg
    if (arg_index < argc - 1) {
      write(STDOUT_FILENO, " ", 1); // write one bite
    }
  }

  if (new_line_flag) {
    ssize_t written = write(STDOUT_FILENO, "\n", 1);
    if (written == -1) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
