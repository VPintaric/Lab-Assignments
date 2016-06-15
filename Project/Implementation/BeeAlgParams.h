#define MAX_SOLUTION 100
#define MIN_SOLUTION 0
#define N_VARIABLES 3
#define N_SCOUTS 200
#define N_BEST 50
#define N_FORAGERS_TO_BEST 500
#define STARTING_SEARCH_AREA 100.0
#define N_GENERATIONS 100

/*
- MAX_SOLUTION:
	Max value of each variable, e.g. if set to '100' and there are 3 variables of the function being optimized
	maximum possible value of each variable will be '100' (algorithm won't search for solutions greater than that).

- MIN_SOLUTION:
	Same as for MAX_SOLUTION parameter only it indicates the minimum value of variables.

- N_VARIABLES:
	Number of variables of the function being optimized
	NOTE: this parameter could be obtained through parsing of the fitness function as it directly
	depends upon the function.
	NOTE: If this parameter is set as a floating point it is rounded down.

- N_SCOUTS:
	Number of bee scouts being sent over the whole search area (each variable of the solution is being randomly
	selected as x : MIN_SOLUTION <= x <= MAX_SOLUTION) in the start of every generation

- N_BEST:
	Number of scouts selected as being best, for example if N_SCOUTS = 20 and N_BEST = 5,
	after sending all of the non-best scouts in the beginning of the generation algorithm
	will select 5 best bee scouts out of all current scouts thus making updating the
	best scouts group.

- N_FORAGERS_TO_BEST:
	Indicates the amount of foragers which will be given to each best scout
	to search the local area around each scout, e.g. if set to 10 each selected best
	scout in current generation will be given 10 foragers to additionaly search his local
	area limited by his current search area (see the code documentation for additional explanation)

- STARTING_SEARCH_AREA:
	When created, every scout has his local search area (used by foragers assigned to this scout)
	set to this value.

- N_GENERATIONS:
	Number of generations (iterations) this algorithm will go through.
*/
