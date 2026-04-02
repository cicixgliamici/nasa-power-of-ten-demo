#include <stdio.h>

void read_line_bad(char *buffer, int size)
{
    fgets(buffer, size, stdin);
}
