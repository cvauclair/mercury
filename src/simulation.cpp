#include "simulation.h"

Simulation::Simulation()
{

}

Simulation::Simulation(unsigned int popSize, unsigned int goodsNb)
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
		this->agents.push_back(agent);

		// Increment job counter
		jobId++;
		if(jobId == jobsNum){
			jobId = 0;
		}
	}

	// Init RNG
	srand(time(NULL));
}

Simulation::~Simulation()
{

}

unsigned int Simulation::getCurrentDay()
{
	return currentDay;
}

void Simulation::resolveOffers()
{
		// Collect stats
//		this->dayStats->asksNb[goodId] = this->asks[goodId].size();
//		this->dayStats->bidsNb[goodId] = this->bids[goodId].size();
//		this->dayStats->fulfilledAsksNb[goodId] = std::count_if(this->asks[goodId].begin(), this->asks[goodId].end(), [](Offer &ask){return ask.fulfilled;});
//		this->dayStats->fulfilledBidsNb[goodId] = std::count_if(this->bids[goodId].begin(), this->bids[goodId].end(), [](Offer &bid){return bid.fulfilled;});
//		if(this->dayStats->quantityTraded[goodId] != 0){
//			this->dayStats->averagePrice[goodId] = this->dayStats->moneyTraded[goodId]/this->dayStats->quantityTraded[goodId];
//		}
//	}
}

