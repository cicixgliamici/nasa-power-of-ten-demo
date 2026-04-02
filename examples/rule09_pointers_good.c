#include <stddef.h>
#include <stdbool.h>

bool write_value_good(int *value_slot, int value)
{
    if (value_slot == NULL)
    {
        return false;
    }

    *value_slot = value;
    return true;
}

int main(void)
{
    int value = 0;
    return write_value_good(&value, 10) ? 0 : 1;
}
