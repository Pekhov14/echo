#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WHITE_SPACE " "

void process_escape_sequences(char *str, int *len) {
  int i = 0;
  int j = 0;
  int original_len = *len;

  while (i < original_len) {
    if (str[i] == '\\' && i + 1 < original_len) {
      switch (str[i + 1]) {
      case 'n':
        str[j++] = '\n';
        i += 2;
        break;
      case 't':
        str[j++] = '\t';
        i += 2;
        break;
      case 'r':
        str[j++] = '\r';
        i += 2;
        break;
      case '\\':
        str[j++] = '\\';
        i += 2;
        break;
      default:
        str[j++] = str[i++];
        break;
      }
    } else {
      str[j++] = str[i++];
    }
  }

  *len = j;
}

int main(int argc, char **argv) {
  int new_line_flag = 1; // 1 - print new line, 0 - do not print new line
  // todo: rename e_flag to escape_sequences_flag
  int e_flag = 0; // 0 - no escape sequences, 1 - process escape sequences
  int arg_index = 1;

  // flags
  // string end in c lang is \0
  while (arg_index < argc && argv[arg_index][0] == '-' &&
         argv[arg_index][1] != '\0') {
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

    arg_index++; // next flag argument
  }

  for (; arg_index < argc; arg_index++) {
    char *current_arg = argv[arg_index];
    int len = strlen(current_arg);

    if (e_flag) {
      process_escape_sequences(current_arg, &len);
    }

    // const void *buf
    ssize_t bytes_written =
        write(STDOUT_FILENO, argv[arg_index], len); // syscall -> kernel
    if (bytes_written == -1) {
      return EXIT_FAILURE;
    }

    // todo: move to funcatin is_last_arg
    if (arg_index < argc - 1) {
      ssize_t space_written =
          write(STDOUT_FILENO, WHITE_SPACE, 1); // write one bite
      if (space_written == -1) {
        return EXIT_FAILURE;
      }
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