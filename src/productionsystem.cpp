#include "productionsystem.h"

// Note: consumption is const since it is defined as such in config.h
void ProductionSystem::doProduction(const std::vector<Job<MAX_GOODS> > &jobs, std::vector<Agent<MAX_GOODS> > &agents, DayStats<MAX_GOODS> *dayStats)
{
	// Variables
	Job<MAX_GOODS> job;

	for(Agent<MAX_GOODS> &agent : agents){
		// Get the agent's job
		job = jobs[agent.jobId];

		// Check if inputs are present in agent's stockpile
		for(int goodId = 0; goodId < MAX_GOODS; goodId++){
			if(agent.stockpile[goodId] < job.inputs[goodId]){
				// If not enough inputs, continue to next agent
				continue;
			}
		}

		// Execute the production
		for(int goodId = 0; goodId < MAX_GOODS; goodId++){
			agent.stockpile[goodId] -= job.inputs[goodId];
			agent.stockpile[goodId] += job.ouputs[goodId];

			// Add quantity to stats
			dayStats->quantityConsumed[goodId] += job.inputs[goodId];
			dayStats->quantityProduced[goodId] += job.ouputs[goodId];
		}
	}
}
