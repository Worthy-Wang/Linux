#include <Unixfunc.h>
#include <iostream>
using namespace std;

int main()
{
    execl("./add", "add" , "1", "2", NULL);
    return 0;
}