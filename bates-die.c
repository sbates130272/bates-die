#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/time.h>

struct stats {
	struct timeval starttime;
	unsigned long seed;
	unsigned long *wins;
	unsigned long games;
};
	
int main(int argc, char **argv)
{
	struct stats mystats;

	mystats.seed = 0;
	
	return 0;
}
