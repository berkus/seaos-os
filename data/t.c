#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
extern void test_function();
int main(int c, char **a)
{
	char *path = getenv("testvar");
	printf(">> %s <<\n", path);
	printf("You can't fight in here! This is the war room!\n");
	return 0;
}
