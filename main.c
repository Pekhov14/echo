#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WHITE_SPACE " "

int is_last_arg(int arg_index, int argc) { return arg_index == argc - 1; }

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
  int escape_sequences_flag =
      0; // 0 - no escape sequences, 1 - process escape sequences
  int arg_index = 1;

  // string end in C lang is \0
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
        escape_sequences_flag = 1;
        break;
      case 'E':
        escape_sequences_flag = 0;
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

  size_t total_estimated_size = 0;
  for (int i = arg_index; i < argc; i++) {
    total_estimated_size += strlen(argv[i]);
    if (!is_last_arg(i, argc)) {
      total_estimated_size += 1; // separator space
    }
  }
  if (new_line_flag) {
    total_estimated_size += 1; // new line
  }

  // Allocate buffer. In C, malloc returns void*
  char *buffer = malloc(total_estimated_size);
  if (!buffer) {
    return EXIT_FAILURE;
  }

  size_t current_buffer_offset = 0;

  for (; arg_index < argc; arg_index++) {
    char *current_arg = argv[arg_index];
    int len = strlen(current_arg);

    if (escape_sequences_flag) {
      process_escape_sequences(current_arg, &len);
    }

    memcpy(buffer + current_buffer_offset, current_arg, len);
    current_buffer_offset += len;

    if (!is_last_arg(arg_index, argc)) {
      buffer[current_buffer_offset++] = ' ';
    }
  }

  if (new_line_flag) {
    buffer[current_buffer_offset++] = '\n';
  }

  ssize_t bytes_written = write(STDOUT_FILENO, buffer, current_buffer_offset);
  free(buffer);

  if (bytes_written == -1) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}