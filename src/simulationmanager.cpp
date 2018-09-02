#include "simulationmanager.h"

SimulationManager::SimulationManager()
{

}

SimulationManager::~SimulationManager()
{

}

void SimulationManager::init(unsigned int popSize)
{
	unsigned int jobsNum = jobs.size();
	unsigned int jobId = 0;

	// Set stats manager
//	this->statsManager = StatsManager::instance();

	// Create agents and rotate the jobs they are given until popSize agents have been created,
	// ensuring an even spread of jobs amongst agents at the start of the simulation
	Agent<MAX_GOODS> agent;
	for(unsigned int i = 0; i < popSize; i++){
		// Init new agent
		agent.balance = 10;
		agent.jobId = jobId;
		for(unsigned int i = 0; i < MAX_GOODS; i++) {agent.stockpile[i] = 1;}
		agent.satisfaction = 1.0;
		for(unsigned int i = 0; i < MAX_GOODS; i++) {agent.offerPrice[i] = 1.0;}
		for(unsigned int i = 0; i < MAX_GOODS; i++) {agent.lastOfferFulfilled[i] = true;}

		// Add new agent
		simulation.agents.push_back(agent);

		// Increment job counter
		jobId++;
		if(jobId == jobsNum){
			jobId = 0;
		}
	}

	// Init RNG
	srand(time(NULL));
}

void SimulationManager::run(unsigned int days)
{
	// Run the simulation for specified amount of days
	for(unsigned int day = 0; day < days; day++){
		this->updateSimulation();
		this->updateAgents();
		this->statsManager.compileDailyStats(this->simulation);
	}

	// Save stats
	this->statsManager.exportStats("stats.csv");
}

void SimulationManager::updateSimulation()
{
	// Clear simulation daily data
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		this->simulation.quantityConsumed[goodId] = 0;
		this->simulation.quantityProduced[goodId] = 0;
		this->simulation.quantityTraded[goodId] = 0;
		this->simulation.moneyTraded[goodId] = 0;

		// Clear offers
		this->simulation.asks[goodId].clear();
		this->simulation.bids[goodId].clear();
	}

	// Update simulation state
	ProductionSystem::doProduction(this->simulation);
	ConsumptionSystem::doConsumption(this->simulation);
	MarketSystem::generateOffers(this->simulation);
	MarketSystem::resolveOffers(this->simulation);
}

void SimulationManager::updateAgents()
{
	// Market feedback
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		// Update asks
		for(Offer &ask : this->simulation.asks[goodId]){
			if(!ask.fulfilled){
				// Reduce price by price change factor
				this->simulation.agents[ask.agentId].offerPrice[goodId] *= 1.0 - PRICE_CHANGE_FACTOR;
			}
			this->simulation.agents[ask.agentId].lastOfferFulfilled[goodId] = ask.fulfilled;
		}
		// Update bids
		for(Offer &bid : this->simulation.bids[goodId]){
			if(!bid.fulfilled){
				// Increase price by price change factor
				this->simulation.agents[bid.agentId].offerPrice[goodId] *= 1.0 + PRICE_CHANGE_FACTOR;
			}
			this->simulation.agents[bid.agentId].lastOfferFulfilled[goodId] = bid.fulfilled;
		}
	}

	// Get good that sold for the most yesterday
//	DayStats<MAX_GOODS> *d = this->statsManager.getDayStats(this->currentDay - 1);
//	unsigned int mostProfitableGoodId = 0;
//	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
//		if(d->averagePrice[goodId] > d->averagePrice[mostProfitableGoodId]){
//			mostProfitableGoodId = goodId;
//		}
//	}

	// Find the job(s) that produce that most profitable good
//	std::vector<unsigned int> mostProfitableJobIds;
//	for(int jobId = 0; jobId < jobs.size(); jobId++){
//		if(jobs[jobId].ouputs[mostProfitableGoodId] > 0){
//			mostProfitableJobIds.push_back(jobId);
//		}
//	}

	// Execute job changing
	for(Agent<MAX_GOODS> &agent : this->simulation.agents){
		if(agent.satisfaction < SATISFACTION_THRESHOLD){
			// Change job
			agent.jobId = rand() % jobs.size();
		}
	}
}
