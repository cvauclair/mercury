#include "simulation.h"

Simulation::Simulation(unsigned int popSize)
{
	unsigned int jobsNum = jobs.size();
	unsigned int jobId = 0;

	// Create agents and rotate the jobs they are given until popSize agents have been created,
	// ensuring an even spread of jobs amongst agents at the start of the simulation
	Agent a;
	for(int i = 0; i < popSize; i++){
		// Init new agent
		a.balance = 10;
		a.jobId = jobId;
		for(int i = 0; i < MAX_GOODS; i++) {a.stockpile[i] = 1;}
		a.satisfaction = 1.0;
		for(int i = 0; i < MAX_GOODS; i++) {a.offerPrice[i] = 1.0;}
		for(int i = 0; i < MAX_GOODS; i++) {a.lastOfferFulfilled[i] = true;}

		// Add new agent
		this->agents.push_back(a);

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

void Simulation::run(unsigned int days)
{
	this->statsManager.init(days);

	for(this->currentDay = 0; this->currentDay < days; this->currentDay++){
		// Init the stats data struct for today
		this->dayStats = this->statsManager.getDayStats(this->currentDay);

		this->doConsumption();

		this->doProduction();

		this->generateOffers();

		this->resolveOffers();

		this->updateAgents();
	}
}

unsigned int Simulation::getCurrentDay()
{
	return currentDay;
}

StatsManager &Simulation::getStatsManager()
{
	return statsManager;
}

void Simulation::doProduction()
{
	// Variables
	Job j;

	for(Agent &a : this->agents){
		// Get the agent's job
		j = jobs[a.jobId];

		// Check if inputs are present in agent's stockpile
		for(int i = 0; i < MAX_GOODS; i++){
			if(a.stockpile[i] < j.inputs[i]){
				// If not enough inputs, continue to next agent
				continue;
			}
		}

		// Execute the production
		for(int i = 0; i < MAX_GOODS; i++){
			a.stockpile[i] -= j.inputs[i];
			a.stockpile[i] += j.ouputs[i];

			// Add quantity to stats
			this->dayStats->quantityConsumed[i] += j.inputs[i];
			this->dayStats->quantityProduced[i] += j.ouputs[i];
		}
	}
}

// Consumption works differently than production as consumption can be partly fulfilled
// unlike the input requirements for a job. The proportion of fulfilled consumption
// will be fed to the agent's learning algorithm.
void Simulation::doConsumption()
{
	// Variables
	unsigned int totalConsumption = 0;
	unsigned int goodsConsumed = 0;
	unsigned int limit = 0;

	for(Agent &a : this->agents){
		// Reset variables
		totalConsumption = goodsConsumed = limit = 0;

		// Calculate total consumption
		for(int i = 0; i < MAX_GOODS; i++){
			totalConsumption += consumption[i];
		}

		// Execute the consumption
		for(int i = 0; i < MAX_GOODS; i++){
			limit = std::min(a.stockpile[i], consumption[i]);
			a.stockpile[i] -= limit;
			goodsConsumed += limit;

			// Add quantity to stats
			this->dayStats->quantityConsumed[i] += limit;
		}

		// Set the agent's satisfaction
		a.satisfaction = goodsConsumed/totalConsumption;
	}
}

void Simulation::generateOffers()
{
	// Variables
	int needs[MAX_GOODS] = {0};
	unsigned int totalNeeds = 0;

	unsigned int popSize = this->agents.size();
	for(int agentId = 0; agentId < popSize; agentId++){
		// Reset variables
		for(int goodId = 0; goodId < MAX_GOODS; goodId++) {needs[goodId] = 0;}

		// Get all needs (negative need is a surplus to be sold)
		for(int goodId = 0; goodId < MAX_GOODS; goodId++){
			needs[goodId] = 2 * (jobs[this->agents[agentId].jobId].inputs[goodId] + consumption[goodId]) - this->agents[agentId].stockpile[goodId];

			// Add to total positive needs if positive
			if(needs[goodId] > 0){
				totalNeeds += needs[goodId];
			}
		}

		// Set bids prices


		// Generate offers (agents will ask for twice their needs)
		for(int i = 0; i < MAX_GOODS; i++){
			if(needs[i] > 0){
				this->generateBid(agentId, i, getPrice(agentId, i, false), needs[i]);
			}else if(needs[i] < 0){
				this->generateAsk(agentId, i, getPrice(agentId, i, true), -1 * needs[i]);
			}

		}
	}
}

float Simulation::getPrice(unsigned int agentId, unsigned int goodId, bool isSelling)
{
	if(this->agents[agentId].lastOfferFulfilled[goodId] == true){
		// If last offer was fulfilled, maintain same price
		return this->agents[agentId].offerPrice[goodId];
	}else{
		// If last offer was unfulfilled, adjust price depending on wether or not agent is selling or not
		if(isSelling){
			return this->agents[agentId].offerPrice[goodId] * (1 - PRICE_CHANGE_FACTOR);
		}else{
			return this->agents[agentId].offerPrice[goodId] * (1 + PRICE_CHANGE_FACTOR);
		}
	}
}

void Simulation::generateAsk(unsigned int agentId, unsigned int goodId, float price, unsigned int quantity)
{
//	this->agents[agentId].wasSelling[goodId] = true;
	this->asks[goodId].push_back({agentId, price, quantity, false});
}

void Simulation::generateBid(unsigned int agentId, unsigned int goodId, float price, unsigned int quantity)
{
//	this->agents[agentId].wasSelling[goodId] = false;
	this->bids[goodId].push_back({agentId, price, quantity, false});
}

void Simulation::resolveOffers()
{
	// Temporary variables
	int quantityTraded = 0;
	float clearingPrice = 0;
	float money = 0;
	std::vector<Offer>::iterator ask;
	std::vector<Offer>::iterator bid;

	// For each good
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		// Sort asks and in increasing order of prices and bids in decreasing order
		std::sort(this->asks[goodId].begin(), this->asks[goodId].end(), [](Offer &ask1, Offer &ask2){return ask1.price < ask2.price;});
		std::sort(this->bids[goodId].begin(), this->bids[goodId].end(), [](Offer &bid1, Offer &bid2){return bid1.price > bid2.price;});

		// Init iterators
		ask = this->asks[goodId].begin();
		bid = this->bids[goodId].begin();

		// Resolve offers
		while(ask != this->asks[goodId].end() & bid != this->bids[goodId].end()){
			// Go to next bid if the bidder cannot afford to buy (works since asks (i.e.: seller offers) are ordered by price)
			if((*bid).price < (*ask).price){
				(*bid).fulfilled = false;
				std::advance(bid, 1);
				continue;
			}

			// Get quantity that will trade hands
			quantityTraded = std::min((*bid).quantity, (*ask).quantity);

			// Get price of transaction
			clearingPrice = (*ask).price;

			// Execute transaction
			if(quantityTraded > 0){
				// Update offers
				(*ask).quantity -= quantityTraded;
				(*bid).quantity += quantityTraded;
//				std::cout << "Offer resolved: " << quantityTraded << " goods traded for " << clearingPrice << "$/unit" << std::endl;

				// Transfer quantityTraded of good from seller agent to buyer agent
				this->agents[(*ask).agentId].stockpile[goodId] -= quantityTraded;
				this->agents[(*bid).agentId].stockpile[goodId] += quantityTraded;

				// Transfer clearingPrice * quantityTraded money from buyer agent to seller agent
				money = clearingPrice * quantityTraded;
				this->agents[(*ask).agentId].balance += money;
				this->agents[(*bid).agentId].balance -= money;

				// Collect data
				this->dayStats->quantityTraded[goodId] += quantityTraded;
				this->dayStats->moneyTraded[goodId] += money;
			}

			// Remove ask from list if seller has sold he wanted inventory
			if((*ask).quantity == 0){
				(*ask).fulfilled = true;
				std:advance(ask,1);
			}

			// Remove bid from list if buyer has gotten all he wanted
			if((*bid).quantity == 0){
				(*bid).fulfilled = true;
				std::advance(bid, 1);
			}
		}

		// Collect stats
		this->dayStats->asksNb[goodId] = this->asks[goodId].size();
		this->dayStats->bidsNb[goodId] = this->bids[goodId].size();
		this->dayStats->fulfilledAsksNb[goodId] = std::count_if(this->asks[goodId].begin(), this->asks[goodId].end(), [](Offer &ask){return ask.fulfilled;});
		this->dayStats->fulfilledBidsNb[goodId] = std::count_if(this->bids[goodId].begin(), this->bids[goodId].end(), [](Offer &bid){return bid.fulfilled;});
		if(this->dayStats->quantityTraded[goodId] != 0){
			this->dayStats->averagePrice[goodId] = this->dayStats->moneyTraded[goodId]/this->dayStats->quantityTraded[goodId];
		}
	}

	// Clear offers
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		this->asks[goodId].clear();
		this->bids[goodId].clear();
	}
}

void Simulation::updateAgents()
{
	// Market feedback
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		// Update asks
		for(Offer &ask : this->asks[goodId]){
			this->agents[ask.agentId].lastOfferFulfilled[goodId] = ask.fulfilled;
		}
		// Update bids
		for(Offer &bid : this->bids[goodId]){
			this->agents[bid.agentId].lastOfferFulfilled[goodId] = bid.fulfilled;
		}
	}

	// Get good that sold for the most yesterday
	DayStats *d = this->statsManager.getDayStats(this->currentDay - 1);
	unsigned int mostProfitableGoodId = 0;
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		if(d->averagePrice[goodId] > d->averagePrice[mostProfitableGoodId]){
			mostProfitableGoodId = goodId;
		}
	}

	// Find the job(s) that produce that most profitable good
	std::vector<unsigned int> mostProfitableJobIds;
	for(int jobId = 0; jobId < jobs.size(); jobId++){
		if(jobs[jobId].ouputs[mostProfitableGoodId] > 0){
			mostProfitableJobIds.push_back(jobId);
		}
	}

	// Execute job changing
	for(Agent &a : this->agents){
		if(a.satisfaction < SATISFACTION_THRESHOLD){
			// Change job
			a.jobId = rand() % jobs.size();
		}
	}
}

void Simulation::compileDailyStats()
{
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		this->dayStats->asksNb[goodId] = this->asks[goodId].size();
		this->dayStats->bidsNb[goodId] = this->bids[goodId].size();
		this->dayStats->fulfilledAsksNb[goodId] = std::count_if(this->asks[goodId].begin(), this->asks[goodId].end(), [](Offer &ask){return ask.fulfilled;});
		this->dayStats->fulfilledBidsNb[goodId] = std::count_if(this->bids[goodId].begin(), this->bids[goodId].end(), [](Offer &bid){return bid.fulfilled;});
		if(this->dayStats->quantityTraded[goodId] != 0){
			this->dayStats->averagePrice[goodId] = this->dayStats->moneyTraded[goodId]/this->dayStats->quantityTraded[goodId];
		}
	}
}
