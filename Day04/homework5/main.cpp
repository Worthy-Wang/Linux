#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <iostream>
#include <iomanip>
#include <pwd.h>
using namespace std;

/*
实现 ls -l命令
传递任意一个目录路径，能够显示该目录的ls -l的效果
*/

//打印文件权限
void printPriority(struct stat statinfo)
{
    mode_t mode = statinfo.st_mode;
    //判断文件类型
    cout << (S_ISDIR(mode) ? 'd' : '-');

    //判断USR权限
    cout << (mode & S_IRUSR ? 'r' : '-');
    cout << (mode & S_IWUSR ? 'w' : '-');
    cout << (mode & S_IXUSR ? 'x' : '-');

    //判断GRP权限
    cout << (mode & S_IRGRP ? 'r' : '-');
    cout << (mode & S_IWGRP ? 'w' : '-');
    cout << (mode & S_IXGRP ? 'x' : '-');

    //判断OTH权限
    cout << (mode & S_IROTH ? 'r' : '-');
    cout << (mode & S_IWOTH ? 'w' : '-');
    cout << (mode & S_IXOTH ? 'x' : '-');

    cout << " ";
}

//打印owner 与 group
void printOwner(struct stat statinfo)
{
    struct passwd *passwdinfo = getpwuid(statinfo.st_uid);
    cout << passwdinfo->pw_name << " ";
    passwdinfo = getpwuid(statinfo.st_gid);
    cout << passwdinfo->pw_name << " ";
}

//打印文件大小
void printSize(struct stat statinfo)
{
    cout << setw(6) << statinfo.st_size << " ";
}

//打印时间
void printTime(struct stat statinfo)
{
    time_t rawtime = statinfo.st_mtime;
    struct tm *timeinfo = localtime(&rawtime);
    cout << timeinfo->tm_mon + 1 << "月 " << timeinfo->tm_mday << "日 ";
    if (timeinfo->tm_hour < 9)
        cout << "0" << timeinfo->tm_hour << ":";
    else
        cout << timeinfo->tm_hour << ":";
    
    if (timeinfo->tm_min < 9)
        cout << "0" << timeinfo->tm_min << " ";
    else
        cout << timeinfo->tm_min << " ";
}

void printName(const char* name)
{
    cout << name << " ";
}

void ls_l(const char *path)
{
    chdir(path);
    DIR *dir = opendir(".");
    struct dirent *dirinfo;
    while (dirinfo = readdir(dir))
    {
        if (!strcmp(dirinfo->d_name, ".") || !strcmp(dirinfo->d_name, ".."))
            continue;
        struct stat statinfo;
        stat(dirinfo->d_name, &statinfo);
        //begin
        printPriority(statinfo);
        printOwner(statinfo);
        printSize(statinfo);
        printTime(statinfo);
        printName(dirinfo->d_name);        
        //end
        cout << endl;
    }
}

int main()
{
    ls_l("/home/wwx/Linux/Day04/fileSystem");
    return 0;
}