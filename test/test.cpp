#include <iostream>

#include "simulation.h"

#include "config.h"

using namespace std;

int main(int argc, char *argv[])
{
	Simulation sim(20);
	StatsManager &sManager = sim.getStatsManager();

	unsigned int days = 40;

	sim.run(days);

	for(int i = 0; i < days; i++){
		sManager.print(i);
	}

	return 0;
}
