#include <func.h>

int main()
{
	printf("I am execute execl\n");
	execl("./print","print1","first","second",NULL);
	printf("you can't see me\n");
}
