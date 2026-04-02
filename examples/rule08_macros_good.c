static int square_good(int x)
{
    return x * x;
}

static int double_and_add_good(int a, int b)
{
    return (a * 2) + (b * 2);
}

int main(void)
{
    return square_good(2) + double_and_add_good(1, 2);
}
