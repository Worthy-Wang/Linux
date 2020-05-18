#include <Unixfunc.h>
#include <iostream>
using namespace std;

//read.cpp
int main()
{
    int fdr = open("pipe", O_RDONLY);
    ERROR_CHECK(fdr, -1, "open r");
    char buf[100] = {0};
    int ret;
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        ret = read(fdr, buf, sizeof(buf));
        if (ret == 0)
        {
            cout << "byebye" << endl;
            break;
        }
        cout << "ret = " << ret << endl;
        cout << "buf = " << buf << endl;
    }
    return 0;
}