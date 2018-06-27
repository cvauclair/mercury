#ifndef PRODUCTIONSYSTEM_H
#define PRODUCTIONSYSTEM_H

#include "statsmanager.h"

class ProductionSystem{
	public:
		static void doProduction(const std::vector<Job<MAX_GOODS>> &jobs, std::vector<Agent<MAX_GOODS>> &agents, DayStats<MAX_GOODS> *dayStats);
};

#endif
