# get_next_line

A C exercise from the 42 curriculum for reading a file descriptor one line at a time.

## Interface

```c
char *get_next_line(int fd);
```

The implementation reads into a static buffer and builds an allocated string for each line. The caller owns each returned string and must free it. Calls continue until the function returns `NULL`.

This repository contains [get_next_line.c](get_next_line.c) and its [header](get_next_line.h), with no Makefile or standalone program. `BUFFER_SIZE` is defined as `1` inside the source. The buffer and index are shared across calls; this version does not maintain separate state for multiple file descriptors.

## Build and usage

Requires a C compiler and the POSIX `read` API. Create `example.c` in the repository root:

```c
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line;

    while ((line = get_next_line(0)) != NULL)
    {
        fputs(line, stdout);
        free(line);
    }
    return (0);
}
```

```sh
cc -Wall -Wextra -Werror example.c get_next_line.c -o example
printf 'first line\nsecond line\n' | ./example
```

The example reads standard input. A descriptor returned by `open` can be passed instead; close it after use.

## Concepts practiced

File descriptors, buffered input, static storage, dynamic allocation, end-of-file handling, and ownership of returned data.
