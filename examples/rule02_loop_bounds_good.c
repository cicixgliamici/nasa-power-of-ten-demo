#include <stddef.h>

#define MAX_TEXT_LENGTH 64U

size_t string_length_good(const char *text)
{
    size_t i;

    if (text == NULL)
    {
        return 0U;
    }

    for (i = 0U; i < MAX_TEXT_LENGTH; i++)
    {
        if (text[i] == '\0')
        {
            return i;
        }
    }

    return MAX_TEXT_LENGTH;
}

int main(void)
{
    return 0;
}
