#include <iostream>
#include <stdio.h>

//#include "simulationmanager.h"
#include "configloader.h"

using namespace std;

int main(int argc, char *argv[]){
	ConfigLoader configLoader;
	configLoader.loadConfig();

	//	SimulationManager simulationManager;

//	simulationManager.init(30);
//	simulationManager.run(80);

	return 0;
}
