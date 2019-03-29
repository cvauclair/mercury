#ifndef CONSUMPTIONSYSTEM_H
#define CONSUMPTIONSYSTEM_H

#include <vector>
//#include "config.h"
#include "definitions.h"
#include "statsmanager.h"

#include "simulation.h"

class ConsumptionSystem{
	public:
		static void doConsumption(Simulation &simulation);
};

#endif
