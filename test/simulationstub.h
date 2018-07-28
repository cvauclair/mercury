#ifndef SIMULATIONSTUB_H
#define SIMULATIONSTUB_H

#include "testconfig.h"

// Simulation stub class that initializes the basic data needed to run tests
class SimulationStub{
	public:
		SimulationStub()
		{

		}

		~SimulationStub();

	private:
		// Agents
		std::vector<Agent<MAX_GOODS>> agents;
};

#endif
