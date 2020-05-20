#include <iostream>
#include <Unixfunc.h>
using namespace std;

int main()
{
    char *buf = (char *)malloc(sizeof(char) * 5);
    strcpy(buf, "hello");
    if (fork() > 0)
    {
        printf("%x\n", buf);
        cout << buf << endl;
        wait(NULL);
    }
    else
    {
        buf[0] = 'H';
        printf("%x\n", buf);
        cout << buf << endl;
    }

    return 0;
}