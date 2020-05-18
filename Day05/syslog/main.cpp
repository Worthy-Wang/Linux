#include <iostream>
#include <Unixfunc.h>
#include <syslog.h>
using namespace std;

/*
linux日志
日志存放在 /var/log/syslog 文件中

* 头文件：#include <syslog.h>
* void syslog(int priority, const char* msg);
调用syslog函数之后自动向 /var/log/syslog 文件中进行输出。

*/

int main()
{
    syslog(LOG_DEBUG, "this is debug message\n");
    syslog(LOG_INFO, "this is info message\n");
    syslog(LOG_NOTICE, "this is notice message\n");
    syslog(LOG_WARNING, "this is warining message\n");
    syslog(LOG_ERR, "this is error message\n");
    syslog(LOG_CRIT, "this is crit message\n");
    syslog(LOG_ALERT, "this is alert message\n");
    syslog(LOG_EMERG, "this is emerge message\n");
    return 0;
}