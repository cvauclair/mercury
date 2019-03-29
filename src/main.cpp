#include <iostream>
#include <stdio.h>

#include "simulationmanager.h"
#include "utility/logger.h"

using namespace std;

int main(int argc, char *argv[]){
	try {
		SimulationManager simulationManager;

		simulationManager.init(30);
		simulationManager.run(80);
	} catch (std::exception &e) {
		Logger::log("Error", e.what(), true);
	}
	return 0;
}
