#include <iostream>

int main()
{
    int *a = new int;
    free(a);
    return 0;
}