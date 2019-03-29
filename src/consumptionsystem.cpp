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
void ConsumptionSystem::doConsumption(Simulation &simulation)
{
	// Variables
	unsigned int totalConsumption = 0;
	unsigned int goodsConsumed = 0;
	unsigned int limit = 0;

	for(Agent &agent : simulation.agents){
		// Reset variables
		totalConsumption = goodsConsumed = limit = 0;

		// Calculate total consumption
		for(unsigned int goodId = 0; goodId < simulation.goods.size(); goodId++){
			totalConsumption += consumption[goodId];
		}

		// Execute the consumption
		for(unsigned int goodId = 0; goodId < simulation.goods.size(); goodId++){
			limit = std::min(agent.stockpile[goodId], consumption[goodId]);
			agent.stockpile[goodId] -= limit;
			goodsConsumed += limit;

			simulation.quantityConsumed[goodId] += limit;
		}

		// Set the agent's satisfaction
		agent.satisfaction = goodsConsumed/totalConsumption;
	}

}
