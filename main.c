#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WHITE_SPACE " "

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    // const void *buf
    ssize_t written =
        write(STDOUT_FILENO, argv[i], strlen(argv[i])); // syscall -> kernel
    if (written == -1) {
      return -1; // Error
    }

    // todo: move to funcatin is_last_arg
    if (i < argc - 1) {
      write(STDOUT_FILENO, " ", 1); // write one bite
    }
  }

  write(STDOUT_FILENO, "\n", 1);

  return EXIT_SUCCESS;
}
