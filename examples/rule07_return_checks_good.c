#include <stdio.h>
#include <stdbool.h>

bool read_line_good(char *buffer, int size)
{
    if ((buffer == NULL) || (size <= 0))
    {
        return false;
    }

    if (fgets(buffer, size, stdin) == NULL)
    {
        return false;
    }

    return true;
}

int main(void)
{
    return 0;
}
