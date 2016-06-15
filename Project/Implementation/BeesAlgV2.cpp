#include<iostream>
#include<cmath>
#include "BeeAlgParams.h"
#include<stdlib.h>
#include<time.h>
using namespace std;


/*Bees algorithm can be used for continuous optimization problems,
	not sure how it could be used for discrete optimization -> some implementation problems*/

class Bee {
	double* solution; //which combination of variables is this bee checking for fitness e.g. f(x, y) -> specific x and y are a combination
	double fitness; //the fitness of this bee, should be calculated in the constructor right away
	
	public:
	/* Constructor for a single scout bee, it is randomly set in the whole domain of the solutions */
	Bee(){
		solution = (double*) malloc(N_VARIABLES * sizeof(double)); //allocate memory for N_VARIABLES and randomly assign them
		for(int i = 0; i < N_VARIABLES; i++)
			solution[i] = MIN_SOLUTION + ((double) rand() / RAND_MAX) * (MAX_SOLUTION - MIN_SOLUTION);
		fitness = calculateFitness(solution);
		}
	
	/* Constructor for a single forager bee which is in the area of a given scout bee */
	Bee(Bee* scout, double areaOfSearch){
		solution = (double*) malloc(N_VARIABLES * sizeof(double));
		for(int i = 0; i < N_VARIABLES; i++){
			double max = ((scout->getSolution(i)+areaOfSearch < MAX_SOLUTION) ? (scout->getSolution(i)+areaOfSearch) : MAX_SOLUTION);
			double min = ((scout->getSolution(i)-areaOfSearch > MIN_SOLUTION) ? (scout->getSolution(i)-areaOfSearch) : MIN_SOLUTION);
			solution[i] = min + (((double) rand()) / RAND_MAX) * (max - min);
			}
		fitness = calculateFitness(solution);
		}

	~Bee(){
		free(solution);
		}
	
	double getSolution(int i){ // the solution attribute of Bee instances should be immutable, that's why this function is here
		return solution[i];
		}

	double getFitness(){
		return fitness;
		}

	void print(){
		for(int i = 0; i < N_VARIABLES; i++)
			cout << "x" << i+1 << " = " << solution[i] << " ";
		cout << "fitness = " << fitness;
		}
	
	double calculateFitness(double* vars); // should be user implemented as it depends on the problem
	};

// Class for describing the selected best group of scouts 
class BeeBestGroup {

	// This class is for each selected best scout and is used for encapsulating the given scout
	// and providing the foragers assigned to this scout with information about the search area size
	class ScoutGroup {
		public:
		Bee* scout;
		double area_search_size;
		
		ScoutGroup(){
			scout = new Bee();
			area_search_size = STARTING_SEARCH_AREA;
			}
		
		~ScoutGroup(){
			delete scout;
			}
	};
	ScoutGroup** group; // array of selected best scouts

	public:
	BeeBestGroup(){
		group = (ScoutGroup**) malloc(N_BEST * sizeof(ScoutGroup*));
		for(int i = 0; i < N_BEST; i++)
			group[i] = new ScoutGroup();
		sortScoutsByFitness();
		sendRestOfScouts();
		}
	
	~BeeBestGroup(){
		for(int i = 0; i < N_BEST; i++)
			delete group[i];
		}
	//sort the selected best scouts by fitness, insertion sort
	void sortScoutsByFitness(){
		for(int i = 1; i < N_BEST; i++) {
			ScoutGroup* key = group[i];
			int k = i - 1;
			while(k >= 0 && group[k]->scout->getFitness() > key->scout->getFitness()) {
				group[k + 1] = group[k];
				k--;
		        	}
	        	group[k + 1] = key;
			}
		}

	void sendRestOfScouts(){
		for(int i = 0; i < N_SCOUTS - N_BEST; i++){
			Bee* newScout = new Bee();
			bool goodEnough = false;
			for(int j = 0; j < N_BEST; j++){
				if(group[j]->scout->getFitness() > newScout->getFitness()){
					if(j-1 < 0) break;
					delete group[j-1]->scout;
					goodEnough = true;
					group[j-1]->scout = newScout;
					group[j-1]->area_search_size = STARTING_SEARCH_AREA;
					break;
					}
				}
			if(!goodEnough) delete newScout;
			}
		}

	void sendForagers(){
		for(int i = 0; i < N_BEST; i++){
			bool foragerPromoted = false;
			for(int j = 0; j < N_FORAGERS_TO_BEST; j++){
				Bee* forager = new Bee(group[i]->scout, STARTING_SEARCH_AREA);
				if(forager->getFitness() > group[i]->scout->getFitness()){
					delete group[i]->scout;
					group[i]->scout = forager;
					group[i]->area_search_size = STARTING_SEARCH_AREA;
					foragerPromoted = true;
					}
				else delete forager;
				}
			if(foragerPromoted)
				group[i]->area_search_size /= 1.5f;
			}
		sortScoutsByFitness();
		}
	
	void print(){
		for(int i = 0; i < N_BEST; i++){
			cout << "\tBee #" << i+1 << ": ";
			group[i]->scout->print();
			cout << endl;
			}
		}
	};


double Bee::calculateFitness(double* vars){
	int x = vars[0];
	int y = vars[1];
	int z = vars[2];
	int w = 100 - x - y - z;
	if(w < 0)
		return -10000;
	int calories = 2*x + 9*y + z + 8*w;
	if(calories != 500)
		return -10000;
	int capacity = 3*x - 3*y - z;
	int durability = 3*y;
	int flavor = 4*z - 2*w;
	int texture = -3*x + 2*w;
	if(capacity < 0 || durability < 0 || flavor < 0 || texture < 0)
		return 0;
	else
		return capacity * durability * flavor * texture;
	}

void printErr(const char *err){
	cout << err << endl;
	exit(1);
	}

int main(void){

	//Checking if set parameters in 'BeeAlgParams.h' are correctly set...
	if(MAX_SOLUTION < MIN_SOLUTION)
		printErr("Error: MAX_SOLUTION parameter is lesser than MIN_SOLUTION parameter");
	if(N_VARIABLES <= 0)
		printErr("Error: N_VARIABLES paramater is set to be less than or equal to 0");
	if(N_SCOUTS <= 0)
		printErr("Error: N_SCOUTS parameter is set to be less than or equal to 0");
	if(N_BEST <= 0)
		printErr("Error: N_BEST paramater is set to be less than or equal to 0");
	if(N_FORAGERS_TO_BEST < 0)
		printErr("Error: N_FORAGERS_TO_BEST parameter is set to be less than 0");
	if(STARTING_SEARCH_AREA < 0)
		printErr("Error: STARTING_SEARCH_AREA parameter is set to be less than 0");
	if(N_GENERATIONS <= 0)
		printErr("Error: N_GENERATIONS parameter is set to be less than 0");
	if(N_SCOUTS < N_BEST)
		printErr("Error: N_BEST parameter is set to be less than N_SCOUTS parameter");
	//...parameter checking ends here

	srand((unsigned) time(NULL)); // Seed for random number generator

	BeeBestGroup* best = new BeeBestGroup(); //construction of an object which contains selected best scouts, also it initializes the first population
	cout << "INITIAL POPULATION: " << endl;
	best->print();

	for(int i = 0; i < N_GENERATIONS; i++){
		cout << "---------GENERATION #" << i+1 << "----------" << endl;
		best->sendForagers(); // sends foragers to every best scout, and switches them to be new scouts if they end up being better
		best->sendRestOfScouts(); // sends the rest of scouts (those which are not in the "best group") across the whole search area
		best->print();
		cout << endl << endl;
		}
	
	delete best;
	return 0;
	}
