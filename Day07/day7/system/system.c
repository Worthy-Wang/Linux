#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	system(argv[1]);
	return 0;
}
