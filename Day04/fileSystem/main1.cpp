#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <iostream>
#include <iomanip>
using namespace std;

//一.目录操作
/*
1.获取、改变当前目录
* char* getcwd(char*, size_t)
* int chdir(char*, mode_t)

创建和删除目录
* int mkdir(char*, mode_t)
* int rmdir(char*)

*/

void test1()
{
    cout << "Now working directory is :" << endl;
    cout << getcwd(NULL, 0) << endl;
    if (mkdir("./newdir", 0775))
        cout << "mkdir ERROR" << endl;
    if (chdir("./newdir/"))
        cout << "can't find the directory" << endl;
    cout << getcwd(NULL, 0) << endl;

    if (chdir(".."))
        cout << "can't find the directory" << endl;
    if (rmdir("newdir"))
        cout << "rmdir ERROR" << endl;
}

/*
2.打开目录流、读取目录流、关闭目录流 
* DIR* opendir(char*)
* struct dirent* readdir(char*)
* int closedir(DIR*)
整个与FILE*的文件流十分相似，也很好理解。

*/
void test2()
{
    DIR *dir = opendir("newdir");
    if (!dir)
        cout << "opendir ERROR" << endl;
    struct dirent *dir_info;
    while (dir_info = readdir(dir))
        cout << dir_info->d_name << endl;
    closedir(dir);
}

/*
3.读取文件的类型，大小, 最近访问时间等
* int stat(const char*, struct stat*)
* int fstat(int fd, struct stat*)

struct stat 中最常用的两个字段:
* st_mode 文件类型
* st_size 文件大小

针对st_mode的判断有以下几种：
* S_ISREG(st_mode) 是否为普通文件
* S_ISDIR(st_mode) 是否为目录

*/
void test3()
{
    struct stat stat_info;
    cout << getcwd(NULL, 0) << endl;
    if (stat("newdir", &stat_info))
        cout << "stat ERROR" << endl;

    if (S_ISREG(stat_info.st_mode))
        cout << "file" << endl;
    else if (S_ISDIR(stat_info.st_mode))
        cout << "dir" << endl;

    cout << stat_info.st_size << endl;

    cout << stat_info.st_uid << endl;

    cout << stat_info.st_gid << endl;

    cout << "输出文件的最近依次的访问时间：" << endl;
    //MM DD HH:mm
    time_t rawtime = stat_info.st_atime;
    struct tm *timeinfo = localtime(&rawtime);
    if (timeinfo->tm_min > 9)
        cout << timeinfo->tm_mon + 1 << "月 " << timeinfo->tm_mday << "日 " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl;
    else
        cout << timeinfo->tm_mon + 1 << "月 " << timeinfo->tm_mday << "日 " << timeinfo->tm_hour << ":0" << timeinfo->tm_min << endl;

}

/*
4.实现 tree 命令
以树形结构输出该目录下的文件 
采用DFS的方法输出
*/
void tree(const char *dirname, int depth)
{
    DIR *dir = opendir(dirname);
    if (!dir)
        return;

    chdir(dirname);
    struct dirent *dirbuf;
    while (dirbuf = readdir(dir))
    {
        if (!strcmp(dirbuf->d_name, ".") || !strcmp(dirbuf->d_name, ".."))
            continue;
        else
        {
            cout << "|" << setw(depth) << setfill(' ') << "--" << dirbuf->d_name << endl;
            tree(dirbuf->d_name, depth + 5);
        }
    }
    chdir("..");
    closedir(dir);
}

void test4()
{
    tree("newdir", 0);
}

int main(int argc, char *argv[])
{
    test4();
    return 0;
}
