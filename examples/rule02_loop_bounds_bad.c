#include <stddef.h>

size_t string_length_bad(const char *text)
{
    size_t i = 0U;

    while (text[i] != '\0')
    {
        i++;
    }

    return i;
}
