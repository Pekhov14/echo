#include <string.h>
#include <unistd.h>

/*
 * 0 Standart input
 * 1 Standart output
 * 2 Standart error
 */
#define FILE_DESCRIPTOR 1
#define WHITE_SPACE " "

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    // const void *buf
    ssize_t written =
        write(FILE_DESCRIPTOR, argv[i], strlen(argv[i])); // syscall -> kernel
    if (written == -1) {
      return -1; // Error
    }

    // todo: move to funcatin is_last_arg
    if (i < argc - 1) {
      write(FILE_DESCRIPTOR, " ", 1); // write one bite
    }
  }

  write(FILE_DESCRIPTOR, "\n", 1);

  return 0;
}
