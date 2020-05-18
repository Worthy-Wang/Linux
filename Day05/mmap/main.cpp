#include <Unixfunc.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

/*
前言：为什么要使用mmap内存映射？
我们知道，CPU从 I/O设备 读写的速度非常慢，而从 内存 读写的速度非常快，如果对一个文件需要进行多次读写，那么每一次都调用 I/O 
读写操作时很不划算的，于是我们便将这个文件 映射 到内存中，这样CPU就可以直接快速读写。
mmap内存映射是一种空间换时间的思想。

mmap内存映射
* void* mmap(void* addr, size_t len, int proc, int flags, int fd, off_t offset)

参数说明：
* addr
映射内存的地址，一般设置为NULL，表示系统自动选择内存映射的地址；也可以自己定义内存映射的地址

* len
需要映射的文件的大小

* proc
对映射区域的保护措施
PROT_READ 可读
PROT_WRITE 可写
PROT_EXEC 可执行
PROT_NONE 不能进行存取

* flags
在内存中修改了文件之后是否将修改复制回源文件
MAP_SHARED 映射内存修改后会复制回源文件， 也就是 共享内存 技术
MAP_PRIVATE 映射内存修改后不会回到源文件, 类似于 写时复制（copy on write） 技术

* fd
文件句柄（文件描述符）

* offset
文件偏移, 注意必须是分页大小的整数倍

* 返回值
成功则返回内存映射的起始地址，需要进行(char*)转换，并让一个char*指针指向内存
失败则返回-1，也需要进行(char*)强制转换

*/

/*
案例1：共享内存设计
修改file文件中第一个字母为 'm', 再查看源文件file
*/
int test1()
{
    const char *filename = "file";
    int ret;
    int fd = open(filename, O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    char *file;
    struct stat statinfo;
    ret = stat(filename, &statinfo);
    ERROR_CHECK(ret, -1, "stat");
    file = (char *)mmap(NULL, statinfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK((void *)file, (void *)-1, "mmap");
    cout << file << endl;
    file[0] = 'm';
    cout << file << endl;
    ret = munmap(file, statinfo.st_size);
    ERROR_CHECK(ret, -1, "munmap");
    close(fd);
    return 0;
}

/*
案例2：父子进程的进程间通信
*/
int test2()
{
    int fd = open("file2", O_RDWR | O_CREAT, 0755);
    char *buff = (char*)mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(buff, (char*)-1, "mmap");
    if (fork() == 0)
    {
        sprintf(buff, "%s", "child message");
        exit(0);
    }
    sleep(1);
    cout << "message from child: " << buff << endl;
    exit(0);
}

int main()
{
    test2();
    return 0;
}