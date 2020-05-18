#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <cctype>
#include <algorithm>
#include <climits>
#include <sstream>
#include <deque>
#include <ctime>
using namespace std;

//<ctime>库中的时间的使用

/*
0. struct tm*
使用时间最重要的结构体就是掌握struct tm*的用法
*/
void test0()
{
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);
    cout << timeinfo->tm_year + 1900 << "年" << endl;
    cout << timeinfo->tm_mon + 1 << "月" << endl;
    cout << timeinfo->tm_mday << "日" << endl;
    cout << timeinfo->tm_hour << "时" << endl;
    cout << timeinfo->tm_min << "分" << endl;
    cout << timeinfo->tm_sec << "秒" << endl;
    cout << "星期" << timeinfo->tm_wday << endl;
}

/*
1. char* asctime(const struct tm* timeinfo)
输出格式如下：
Thu May 14 15:18:00 2020
*/
void test1()
{
    time_t rawtime;
    time(&rawtime);
    cout << rawtime << endl;
    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);
    cout << asctime(timeinfo) << endl;
}



int main()
{
    test1();
    return 0;
}