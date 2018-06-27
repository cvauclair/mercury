#ifndef CONSUMPTIONSYSTEM_H
#define CONSUMPTIONSYSTEM_H

#include <vector>
#include "config.h"
#include "definitions.h"
#include "statsmanager.h"

class ConsumptionSystem{
	public:
		static void doConsumption(const std::array<char, MAX_GOODS> &consumption, std::vector<Agent<MAX_GOODS>> &agents, DayStats<MAX_GOODS> *dayStats);
};

#endif
