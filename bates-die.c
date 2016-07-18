#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <sys/time.h>

#include "argconfig.h"

const char program_desc[] = "Simulation of a simple dice game..";

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

static const struct argconfig_commandline_options command_line_options[] = {
	{"seed", "NUM", CFG_LONG, &defaults.seed, required_argument,
			"number of io operations to do"},
	{"n", "NUM", CFG_LONG_SUFFIX, &defaults.ngames, required_argument,
			"number of games to play"},
	{"s", "NUM", CFG_LONG, &defaults.nsides, required_argument,
			"number of sides on the die"},
	{"w", "NUM", CFG_LONG_SUFFIX, &defaults.nwins, required_argument,
			"number of sides needsed to win the game"},
	{0}
};
	
int main(int argc, char **argv)
{
	struct bates_die_t bates_die;

	int args = argconfig_parse(argc, argv, program_desc,
				   command_line_options,
				   &defaults, &bates_die, sizeof(bates_die));

	if (bates_die.seed==0)
		bates_die.seed = time(NULL);
	srand(bates_die.seed);

	gettimeofday(&bates_die.starttime, NULL);
	
	return 0;
}
