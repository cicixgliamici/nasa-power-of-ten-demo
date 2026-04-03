#include <stdio.h>

#define SQUARE(x) x * x

int main(void)
{
    int result = SQUARE(1 + 2);
    printf("%d\n", result);
    return 0;
}
