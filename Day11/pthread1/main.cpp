#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
Posix多线程pthread详解

前言

不论是子线程还是主线程，实质上都共同属于同一个进程，这大大的减小了系统的开销。
另外，多线程与多进程的使用实质上主要掌握 创建 等待 退出 这三个点

||创建|等待|退出|清理|
|多进程|fork|wait|exit|signal|
|多线程|pthread_create|pthread_join|pthread_exit|pthread_cleanup_push(pop)|

一.线程创建 pthread_create

* int pthread_create(pthread_t *__restrict__ __newthread, 
const pthread_attr_t *__restrict__ __attr, 
void *(*__start_routine)(void *), 
void *__restrict__ __arg)

线程创建的过程中有可能需要向子线程传入一些参数类型，那么如何进行传入参数也是多线程的难点之一。

1. 无输入参数

可以看出，主线程与子线程属于同一个进程
*/

void* threadFunc1(void* arg)
{
    cout << "this is child thread, process id = " << getpid() << " , thread id = " << pthread_self() << endl;
    pthread_exit(NULL);
}

void test1()
{
    pthread_t pid;
    cout << "this is main thread, process id = " << getpid() << " , thread id = " << pthread_self() << endl;
    pthread_create(&pid, NULL, threadFunc1, NULL);
    cout << "child thread id = " << pid << endl;
    pthread_join(pid, NULL);
}

/*
2.输入int型参数
*/
void* threadFunc2(void* arg)
{
    cout << "child thread get val:" << *(int*)arg << endl;
    pthread_exit(NULL); 
}

void test2()
{
    pthread_t pid;
    int val = 5;
    pthread_create(&pid, NULL, threadFunc2, (void*)&val);
    pthread_join(pid, NULL);
}

/*
3.输入fd文件描述符
*/
void* threadFunc3(void* arg)
{
    int fd = *(int*)arg;
    cout << "child thread get fd:" << fd << endl;
    close(fd);
    pthread_exit(NULL); 
}

void test3()
{
    pthread_t pid;
    int fd = open("file", O_RDWR | O_CREAT, 0665);
    pthread_create(&pid, NULL, threadFunc3, &fd);
    pthread_join(pid, NULL);
}

/*
4.传入char*类型
*/
void* threadFunc4(void* arg)
{
    char* buf = (char*)arg;
    cout << "child thread is processing buf " << endl;
    buf = (char*)malloc(10 * sizeof(char));
    strcpy(buf, "hello");
    cout << "now buf is " << buf << endl;
    pthread_exit(NULL); 
}

void test4()
{
    pthread_t pid;
    char *buf = NULL;
    pthread_create(&pid, NULL, threadFunc4, buf);
    pthread_join(pid, NULL);
}

/*
5.输入long型参数

此处传入long型参数的方式也可以按照第2种传入的方式来，更为通用
*/
void* threadFunc5(void* arg)
{
    cout << "child thread get val:" << (long)arg << endl;
    pthread_exit(NULL); 
}

void test5()
{
    pthread_t pid;
    long val = 5;
    pthread_create(&pid, NULL, threadFunc2, (void*)val);
    pthread_join(pid, NULL);
}

/*
6.传入结构体
传入学生的姓名，成绩，并打印
*/
struct Student
{
    const char* name;
    double score;
};
void *threadFunc6(void* arg)
{
    Student *stu = (Student*)arg;
    for (int i = 0; i < 3; i++)
        cout << stu[i].name << ":" << stu[i].score << endl;
    pthread_exit(NULL);
}

void test6()
{
    Student stus[3] = {{"wwx", 99}, {"wk", 77}, {"wby", 88}};
    pthread_t pid;
    pthread_create(&pid, NULL, threadFunc6, stus);
    pthread_join(pid, NULL);
}


/*
7.小练习：主线程与子线程各自加一千万，看结果是否为两千万
*/
const int N = 10000000;
void *threadFunc7(void* arg)
{
    for (int i = 0; i < N; i++)
        *(int*)arg += 1;
    pthread_exit(NULL);
}

void test7()
{
    int sum = 0;
    pthread_t pid;
    pthread_create(&pid, NULL, threadFunc7, &sum);
    for (int i = 0; i < N; i++)
        sum ++;
    pthread_join(pid, NULL);
    cout << "final sum = " << sum << endl;
}

int main()
{
    test1();
    return 0;
}