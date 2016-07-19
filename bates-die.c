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
	unsigned nwin;

	unsigned *wins;
	unsigned games;
	unsigned npdf;
};

static const struct bates_die_t defaults = {
	.seed       = 0,
	.ngames     = 100,
	.nsides     = 6,
	.nwin       = 5,
};

static const struct argconfig_commandline_options command_line_options[] = {
	{"seed", "NUM", CFG_LONG, &defaults.seed, required_argument,
			"seed for random number generator"},
	{"n", "NUM", CFG_LONG_SUFFIX, &defaults.ngames, required_argument,
			"number of games to play"},
	{"s", "NUM", CFG_LONG, &defaults.nsides, required_argument,
			"number of sides on the die"},
	{"w", "NUM", CFG_LONG_SUFFIX, &defaults.nwin, required_argument,
			"number of rools of winning sides needsed to win the game"},
	{0}
};

static void setup(struct bates_die_t *bates_die)
{
	bates_die->games = 0;
	bates_die->npdf  = (bates_die->nwin-1)*bates_die->nsides-
		bates_die->nwin;
	bates_die->wins  = calloc(bates_die->npdf, sizeof(*bates_die->wins));
	gettimeofday(&bates_die->starttime, NULL);
}

static void teardown(struct bates_die_t *bates_die)
{
	free(bates_die->wins);
}

static void report(struct bates_die_t *bates_die)
{
	fprintf(stdout,"Bates Die Game Results\n");
	fprintf(stdout,"----------------------\n\n");
	fprintf(stdout,"nsides = %3d : nwin = %4d : ngames = %6d\n",
		bates_die->nsides, bates_die->nwin, bates_die->ngames);
	fprintf(stdout,"Results after %4d games (%d sec)\n",
		bates_die->games, 0);
	for (unsigned i=0; i<bates_die->npdf; i++)
		fprintf(stdout,"pdf[%04d] = %4d\n", i, bates_die->wins[i]);
}

static void play(struct bates_die_t *bates_die)
{
	unsigned roll, rolls = 0, *score;

	score = calloc(bates_die->nsides, sizeof(bates_die->nsides));
	while(1)
	{
		roll = rand() % (bates_die->nsides);
		printf("%d\n", roll);
		score[roll]++;
		rolls++;
		if (score[roll]==bates_die->nwin){
			bates_die->wins[rolls]++;
			bates_die->games++;
			break;
		}
	}
	free(score);
}
	
	
int main(int argc, char **argv)
{
	struct bates_die_t bates_die;

	int args = argconfig_parse(argc, argv, program_desc,
				   command_line_options,
				   &defaults, &bates_die, sizeof(bates_die));

	if (bates_die.seed==0)
		bates_die.seed = time(NULL);
	srand(bates_die.seed);

	setup(&bates_die);
	play(&bates_die);
	report(&bates_die);
	teardown(&bates_die);
	
	return 0;
}
