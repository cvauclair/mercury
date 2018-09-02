#include <iostream>
#include <stdio.h>

#include "simulationmanager.h"

using namespace std;

int main(int argc, char *argv[]){
	SimulationManager simulationManager;

	simulationManager.init(30);
	simulationManager.run(80);

	return 0;
}
