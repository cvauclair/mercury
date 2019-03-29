#include "productionsystem.h"

// Note: consumption is const since it is defined as such in config.h
void ProductionSystem::doProduction(Simulation &simulation)
{
	// Variables
	Job job;
	bool doProduction = true;

	for(Agent &agent : simulation.agents){
		// Get the agent's job
		job = simulation.jobs.at(agent.jobId);

		// Check if inputs are present in agent's stockpile
		doProduction = true;
		for(unsigned int goodId = 0; goodId < simulation.goods.size(); goodId++){
			if(agent.stockpile[goodId] < job.inputs[goodId].second){
				// If not enough inputs, continue to next agent
				doProduction = false;
				break;
			}
		}
		if(!doProduction){
			continue;
		}

		// Execute the production
		for(unsigned int goodId = 0; goodId < simulation.goods.size(); goodId++){
			agent.stockpile[goodId] -= job.inputs[goodId].second;
			agent.stockpile[goodId] += job.outputs[goodId].second;

			simulation.quantityConsumed[goodId] += job.inputs[goodId].second;
			simulation.quantityProduced[goodId] += job.outputs[goodId].second;
		}
	}
}
