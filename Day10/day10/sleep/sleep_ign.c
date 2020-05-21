#include <func.h>

int main()
{
	signal(SIGALRM,SIG_IGN);
	sleep(5);
	return 0;
}
