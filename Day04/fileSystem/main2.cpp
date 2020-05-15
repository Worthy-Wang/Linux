#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
using namespace std;

/*
二.基于文件描述符的文件操作
1.打开关闭文件
* int open(const char*, int , mode_t)
* int close(int)

2.读取，写入文件
* size_t read(int fd, char* buf, size_t size)
* size_t write(int fd, char* buf, size_t size)
*/

//练习：从file1中读取， 再写到file2中
void test1()
{
    int fd1 = open("file1", O_RDWR | O_CREAT, 0755);
    int fd2 = open("file2", O_RDWR | O_CREAT, 0755);
    if (fd1 == -1)
        cout << "fd1 open ERROR" << endl;
    if (fd2 == -1)
        cout << "fd2 open ERROR" << endl;
                
    char buf[1024] = {0};
    int len = 0;    
    while ((len = read(fd1, buf, sizeof(buf))) > 0)
    {
        cout << len << endl;
        write(fd2, buf, len);
        memset(buf, 0, sizeof(buf));
    }

    close(fd1);
    close(fd2);
}


/*
3. 改变文件大小
* int ftruncate(int fd, off_t length)
将文件从length偏移的字节数开始截断
*/
void test3()
{
    int fd = open("file1", O_RDWR);
    ftruncate(fd, 1000);
    close(fd);
}

/*
4.文件定位 与 文件空洞设计
* off_t lseek(int fd, off_t offset, int whence)
whence:
* SEEK_SET
* SEEK_CUR
* SEEK_END

文件空洞设计一般用于共享内存
*/

//文件空洞设计
void test4()
{
    int fd = open("file3", O_RDWR | O_CREAT, 0755);
    lseek(fd, 1024, SEEK_SET);
    write(fd, "HelloWorld", strlen("HelloWorld"));
    close(fd);
}

/*
5.文件描述符的复制 
文件描述符类比智能指针的引用计数，也可以理解成深拷贝
* int dup(int oldfd)
此种方式是自动分配文件描述符（从小到大）
当使用 int fd2 = fd; 语句时, 如果进行 close(fd), 那么fd， fd2指向的文件会立刻关闭
当使用 int fd2 = dup(fd); 语句时， 如果进行了 close(fd), fd2指向的文件因为引用计数仍为1，所以文件不会关闭

* int dup2(int oldfd, int newfd)
此种方式是自己定义新的文件描述符（newfd）

*/
void test5()
{
    int fd = open("file4", O_RDWR | O_CREAT, 0755);
    cout << "fd:" << fd << endl;
    // int fd2 = fd;
    int fd2 = dup(fd);
    cout << "fd2:" << fd2 << endl;
    close(fd);
    char buf[1024];
    read(fd2, buf, sizeof(buf));
    cout << buf << endl;
}

/*
6.标准输入、输出、错误输出
分别代表文件描述符中的0、1、2
关闭文件描述符 1 之后，fd2分配到的就是输出 1 ， 那么无论我们输出什么到输出流中，都不会在屏幕中的显示，而是写在fd2指向的文件中
*/
void test6()
{
    int fd = open("file6", O_RDWR|O_CREAT, 0755);
    cout << "fd:" << fd << endl;
    close(1);//关闭输出
    int fd2 = dup(fd);
    cout << "fd2:" << fd2 << endl;
    cout << "HelloWorld" << endl;
    close(fd);
}


int main(int argc, char *argv[])
{
    test6();
    return 0;
}