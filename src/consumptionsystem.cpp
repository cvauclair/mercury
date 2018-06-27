#include "consumptionsystem.h"

//ConsumptionSystem::ConsumptionSystem(StatsManager *sManager)
//{
//	this->sManager = sManager;
//}

//ConsumptionSystem::~ConsumptionSystem()
//{

//}

// Consumption works differently than production as consumption can be partly fulfilled
// unlike the input requirements for a job. The proportion of fulfilled consumption
// will be fed to the agent's learning algorithm.
// Note: consumption is const since it is defined as such in config.h
void ConsumptionSystem::doConsumption(const std::array<char, MAX_GOODS> &consumption, std::vector<Agent<MAX_GOODS> > &agents, DayStats<MAX_GOODS> *dayStats)
{
	// Variables
	unsigned int totalConsumption = 0;
	unsigned int goodsConsumed = 0;
	unsigned int limit = 0;

	for(Agent<MAX_GOODS> &agent : agents){
		// Reset variables
		totalConsumption = goodsConsumed = limit = 0;

		// Calculate total consumption
		for(int goodId = 0; goodId < MAX_GOODS; goodId++){
			totalConsumption += consumption[goodId];
		}

		// Execute the consumption
		for(int goodId = 0; goodId < MAX_GOODS; goodId++){
			limit = std::min(agent.stockpile[goodId], consumption[goodId]);
			agent.stockpile[goodId] -= limit;
			goodsConsumed += limit;

			// Add quantity to stats
			dayStats->quantityConsumed[goodId] += limit;
		}

		// Set the agent's satisfaction
		agent.satisfaction = goodsConsumed/totalConsumption;
	}
}
