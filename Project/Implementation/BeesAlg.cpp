#include<iostream>
#include<cmath>
#include "BeeAlgParams.h"
#include<stdlib.h>
#include<time.h>
using namespace std;


/*Bees algorithm can be used for continuous optimization problems,
	not sure how it could be used for discrete optimization -> a lot of implementation problems*/

class Bee {
	double* solution; //which combination of variables is this bee checking for fitness e.g. f(x, y) -> specific x and y are a combination
	double fitness; //the fitness of this bee, should be calculated in the constructor right away
	
	public:
	/* Constructor for a single scout bee, it is randomly set in the full domain of the solutions */
	Bee(){
		solution = (double*) malloc(N_VARIABLES * sizeof(double));
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
	
	double getSolution(int i){ // the solution attribute od Bee instances should be immutable, that's why this function is here
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
	
	double calculateFitness(double* vars); // should be implemented later as it depends on the problem
	};

class BeeBestGroup {
	Bee** scouts;

	public:
	BeeBestGroup(){
		scouts = (Bee**) malloc(N_BEST * sizeof(Bee*));
		for(int i = 0; i < N_BEST; i++)
			scouts[i] = new Bee();
		sortScoutsByFitness();
		sendRestOfScouts();
		}
	
	~BeeBestGroup(){
		for(int i = 0; i < N_BEST; i++)
			delete scouts[i];
		}

	void sortScoutsByFitness(){
		for(int i = 1; i < N_BEST; i++) {
			Bee* key = scouts[i];
			int k = i - 1;
			while(k >= 0 && scouts[k]->getFitness() > key->getFitness()) {
				scouts[k + 1] = scouts[k];
				k--;
		        	}
	        	scouts[k + 1] = key;
			}
		}

	void sendRestOfScouts(){
		for(int i = 0; i < N_SCOUTS - N_BEST; i++){
			Bee* newScout = new Bee();
			bool goodEnough = false;
			for(int j = 0; j < N_BEST; j++){
				if(scouts[j]->getFitness() > newScout->getFitness()){
					if(j-1 < 0) break;
					delete scouts[j-1];
					goodEnough = true;
					scouts[j-1] = newScout;
					break;
					}
				}
			if(!goodEnough) delete newScout;
			}
		}

	void sendForagers(){
		for(int i = 0; i < N_BEST; i++){
			for(int j = 0; j < N_FORAGERS_TO_BEST; j++){
				Bee* forager = new Bee(scouts[i], STARTING_SEARCH_AREA);
				if(forager->getFitness() > scouts[i]->getFitness()){
					delete scouts[i];
					scouts[i] = forager;
					}
				else delete forager;
				}
			}
		sortScoutsByFitness();
		}
	
	void print(){
		for(int i = 0; i < N_BEST; i++){
			cout << "\tBee #" << i+1 << ": ";
			scouts[i]->print();
			cout << endl;
			}
		}
	};


double Bee::calculateFitness(double* vars){
	double x = vars[0];
	return -(3*pow(x, 4) + 2*x*x - 15);

	}


int main(void){
	//TODO CHECK IF PARAMETERS ARE OKAY E.G. N_BEST < N_SCOUTS
	srand((unsigned) time(NULL));

	BeeBestGroup* best = new BeeBestGroup();
	cout << "INITIAL POPULATION: " << endl;
	best->print();

	for(int i = 0; i < N_GENERATIONS; i++){
		cout << "---------GENERATION #" << i+1 << "----------" << endl;
		best->sendForagers();
		best->sendRestOfScouts();
		best->print();
		cout << endl << endl;
		}
	
	delete best;
	return 0;
	}
