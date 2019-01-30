#include "productionsystem.h"

// Note: consumption is const since it is defined as such in config.h
void ProductionSystem::doProduction(Simulation &simulation)
{
	// Variables
	Job<MAX_GOODS> job;
	bool doProduction = true;

	for(Agent<MAX_GOODS> &agent : simulation.agents){
		// Get the agent's job
		job = jobs[agent.jobId];

		// Check if inputs are present in agent's stockpile
		doProduction = true;
		for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
			if(agent.stockpile[goodId] < job.inputs[goodId]){
				// If not enough inputs, continue to next agent
				doProduction = false;
				break;
			}
		}
		if(!doProduction){
			continue;
		}

		// Execute the production
		for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
			agent.stockpile[goodId] -= job.inputs[goodId];
			agent.stockpile[goodId] += job.ouputs[goodId];

			simulation.quantityConsumed[goodId] += job.inputs[goodId];
			simulation.quantityProduced[goodId] += job.ouputs[goodId];
		}
	}
}
