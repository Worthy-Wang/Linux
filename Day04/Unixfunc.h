#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <dirent.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#define ARGS_CHECK(argc, val) {if (argc!=val){cout << "ARGS ERROR" << endl; return -1;}}
#define ERROR_CHECK(ret, retval, filename) {if (ret == retval){cout << filename << " ERROR" << endl; return -1;}}  
