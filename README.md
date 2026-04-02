# My Echo

This is a custom implementation of the standard Unix `echo` command written in C. It supports writing arguments to the standard output, with optional flags to control newline behavior and escape sequence interpretation.

## Features

- Prints arguments separated by spaces.
- **`-n` flag**: Do not output the trailing newline.
- **`-e` flag**: Enable interpretation of backslash escapes (e.g., `\n`, `\t`, `\r`, `\\`).
- **`-E` flag**: Disable interpretation of backslash escapes (default behavior).
- Supports combining flags (e.g., `-ne`, `-en`).

## Building

To compile the project, run:

```bash
make
```
This will produce an executable named `echo`.

## Usage

```bash
./echo [OPTIONS]... [STRING]...
```

### Examples

Basic print:
```bash
./echo Hello World
# Output: Hello World
```

No trailing newline:
```bash
./echo -n Hello
# Output: Hello (without extra newline at the end)
```

With escape sequences:
```bash
./echo -e "Line1\nLine2\tIndented"
# Output: 
# Line1
# Line2   Indented
```

Combined flags:
```bash
./echo -ne "Hello\nWorld"
```

## Testing

The project includes an automated test script (`test.sh`). 
To run the automated tests using `Makefile`:

```bash
make test
```
