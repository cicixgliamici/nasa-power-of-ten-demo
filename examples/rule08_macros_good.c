static int square_good(int x)
{
    return x * x;
}

int main(void)
{
    int result = square_good(1 + 2);
    return (result == 9) ? 0 : 1;
}
