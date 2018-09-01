#include <iostream>
#include <stdio.h>

#include "simulation.h"

using namespace std;

int main(int argc, char *argv[]){
	Simulation sim(20, 4);
	StatsManager &sManager = sim.getStatsManager();

	unsigned int days = 80;

	sim.run(days);

	for(int i = 0; i < days; i++){
		sManager.print(i);
	}

	return 0;
}
