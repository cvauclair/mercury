#include <iostream>
#include <stdio.h>

//#include "simulationmanager.h"
#include "configloader.h"

using namespace std;

int main(int argc, char *argv[]){
	ConfigLoader configLoader;
	try {
		configLoader.loadConfig();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	//	SimulationManager simulationManager;

//	simulationManager.init(30);
//	simulationManager.run(80);

	return 0;
}
