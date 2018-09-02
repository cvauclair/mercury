#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "simulation.h"
#include "statsmanager.h"

#include "consumptionsystem.h"
#include "marketsystem.h"
#include "productionsystem.h"

#include "statsmanager.h"

// Class that initiates, oversees and overall manages the simulation as well as other parts of the program (e.g.: data collection)
// Simulation cycle:
//		-Clear offers
//		-Update agents, get agent decision
//		-Update simulation state (production, consumption, market)
//		-Collect stats

class SimulationManager{
	public:
		SimulationManager();
		~SimulationManager();

		void init(unsigned int popSize);
		void run(unsigned int days);

		void updateSimulation();
		void updateAgents();

	private:
		Simulation simulation;
		StatsManager statsManager;
};

#endif
