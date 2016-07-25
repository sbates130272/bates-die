#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <sys/time.h>

#include "argconfig.h"

const char program_desc[] = "Simulation of a simple dice game..";

struct bates_die_t {

	unsigned long seed;
	unsigned long ngames;
	unsigned nsides;
	unsigned nwin;

	struct timeval starttime;
	struct timeval reporttime;
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
	{"s", "NUM", CFG_POSITIVE, &defaults.nsides, required_argument,
			"number of sides on the die"},
	{"w", "NUM", CFG_POSITIVE, &defaults.nwin, required_argument,
			"number of rools of winning sides needsed to win the game"},
	{0}
};

static void setup(struct bates_die_t *bates_die)
{
	bates_die->games = 0;
	bates_die->npdf  = (bates_die->nwin-1)*bates_die->nsides+2;
	bates_die->wins  = calloc(bates_die->npdf, sizeof(*bates_die->wins));
	gettimeofday(&bates_die->starttime, NULL);
}

static void teardown(struct bates_die_t *bates_die)
{
	free(bates_die->wins);
}

static unsigned elapsed(struct bates_die_t *bates_die, unsigned start)
{
	struct timeval current;
	size_t elapsed;
	gettimeofday(&current, NULL);
	if (start){
		elapsed = current.tv_sec - bates_die->starttime.tv_sec;
		return elapsed;
	} else {
		elapsed = current.tv_sec - bates_die->reporttime.tv_sec;
		if (elapsed){
			bates_die->reporttime = current;
			return elapsed;
		}
	}
	return 0;
}

static void report(struct bates_die_t *bates_die)
{
	fprintf(stdout,"Bates Die Game Results\n");
	fprintf(stdout,"----------------------\n\n");
	fprintf(stdout,"seed = %ld : nsides = %d : nwin = %d : ngames = %ld\n",
		bates_die->seed, bates_die->nsides, bates_die->nwin, bates_die->ngames);
	fprintf(stdout,"Results after %4d games (%d sec)\n",
		bates_die->games, elapsed(bates_die, 1));
	for (unsigned i=0; i<bates_die->npdf; i++)
		fprintf(stdout,"pdf[%04d] = %1.8f\n", i, (float)bates_die->wins[i]/bates_die->games);
}


static void play(struct bates_die_t *bates_die)
{
	unsigned roll, rolls = 0, *score;

	score = calloc(bates_die->nsides, sizeof(bates_die->nsides));
	while(1)
	{
		roll = rand() % (bates_die->nsides);
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
	while(1)
	{
		if (bates_die.games >= bates_die.ngames)
			break;
		play(&bates_die);
		if (elapsed(&bates_die, 0))
			report(&bates_die);
	}
	report(&bates_die);
	teardown(&bates_die);
	
	return 0;
}
