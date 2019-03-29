#include <iostream>
#include <stdio.h>

#include "simulationmanager.h"

using namespace std;

int main(int argc, char *argv[]){
	try {
		SimulationManager simulationManager;

		simulationManager.init(30);
		simulationManager.run(80);
	} catch (std::exception &e) {
		std::cout << e.what() <<std::endl;
	}

	return 0;
}
