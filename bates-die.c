#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/time.h>

#include "argconfig.h"

const char program_desc[] = "Simple program for testing ZONE_DEVICE devices.";

struct bates_die_t {
	struct timeval starttime;
	unsigned long seed;
	unsigned ngames;
	unsigned nsides;
	unsigned nwins;
};

static const struct bates_die_t defaults = {
	.seed       = 0,
	.ngames     = 100,
	.nsides     = 6,
	.nwins      = 5,
};

	
int main(int argc, char **argv)
{
	struct bates_die_t bates_die;

	bates_die.seed = 0;
	
	return 0;
}
