#include <Unixfunc.h>
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
    ARGS_CHECK(argc, 3);
    cout << atoi(argv[1]) + atoi(argv[2]) << endl;
    return 0;
}