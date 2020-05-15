#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <iostream>
#include <iomanip>
using namespace std;

/*
传递一个路径名，还有一个文件名，搜索对应路径下是否有该文件，有就打印显示，显示绝对路径。
*/
void findFile(const char* path, const char* filename)
{
    chdir(path);
    DIR *dir = opendir(".");
    struct dirent* dirinfo;
    while (dirinfo = readdir(dir))
        if (!strcmp(dirinfo->d_name, filename))
        {
            cout << path << "/" << filename << endl;
            return;
        }
    cout << "can't find this file" << endl;
}


int main()
{
    findFile("/home/wwx/Linux/Day04/fileSystem", "file1");
    return 0;
}