#include "simulationmanager.h"

SimulationManager::SimulationManager()
{

}

SimulationManager::~SimulationManager()
{

}

void SimulationManager::init(unsigned int popSize)
{
	// Load config data
	this->simulation.goods = ConfigLoader::loadGoodsConfig("/home/christophe/Documents/Programming/mercury/config/goods.lua");
	for(unsigned int goodsId = 0; goodsId < this->simulation.goods.size(); goodsId++){
		this->simulation.goodsIds[this->simulation.goods[goodsId].key] = goodsId;
	}

	this->simulation.numGoods = simulation.goods.size();

	this->simulation.jobs = ConfigLoader::loadJobsConfig("/home/christophe/Documents/Programming/mercury/config/jobs.lua");
	for(unsigned int jobId = 0; jobId < this->simulation.jobs.size(); jobId++){
		this->simulation.jobsIds[this->simulation.jobs[jobId].key] = jobId;
	}

	unsigned int numJobs = this->simulation.jobs.size();
	unsigned int jobId = 0;

	// Create agents and rotate the jobs they are given until popSize agents have been created,
	// ensuring an even spread of jobs amongst agents at the start of the simulation
	Agent agent;
	for(unsigned int i = 0; i < popSize; i++){
		// Init new agent
		agent.balance = 10;
		agent.jobId = jobId;
		for(unsigned int i = 0; i < simulation.numGoods; i++) {agent.stockpile.push_back(1);}
		agent.satisfaction = 1.0;
		for(unsigned int i = 0; i < simulation.numGoods; i++) {agent.offerPrice.push_back(1.0);}
		for(unsigned int i = 0; i < simulation.numGoods; i++) {agent.lastOfferFulfilled.push_back(true);}

		// Add new agent
		simulation.agents.push_back(agent);

		// Increment job counter
		jobId++;
		if(jobId == numJobs){
			jobId = 0;
		}
	}

	// Simulation market data
	this->simulation.asks.assign(this->simulation.goods.size(), {});
	this->simulation.bids.assign(this->simulation.goods.size(), {});
	this->simulation.quantityConsumed.assign(this->simulation.goods.size(), 0);
	this->simulation.quantityProduced.assign(this->simulation.goods.size(), 0);
	this->simulation.quantityTraded.assign(this->simulation.goods.size(), 0);
	this->simulation.moneyTraded.assign(this->simulation.goods.size(), 0.0f);

	// Init stats manager
	this->statsManager.setGoodsIds(this->simulation.goodsIds);
	this->statsManager.setJobsIds(this->simulation.jobsIds);

	// Init RNG
	srand(time(NULL));
}

void SimulationManager::run(unsigned int days)
{
	// Run the simulation for specified amount of days
	for(unsigned int day = 0; day < days; day++){
		this->updateSimulation();
		this->updateAgents();
		this->statsManager.recordStats(this->simulation);
	}

	// Save stats
	this->statsManager.exportStats("stats.csv");
}

void SimulationManager::updateSimulation()
{
	// Clear simulation daily data
	for(unsigned int goodId = 0; goodId < simulation.numGoods; goodId++){
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
	for(unsigned int goodId = 0; goodId < simulation.numGoods; goodId++){
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
	unsigned int mostProfitableGoodId;
	try {
		mostProfitableGoodId = this->statsManager.getMostProfitableGood();
	} catch (std::exception &e) {
		// Do not do any jo changing
		return;
	}

	// Find the job(s) that produce that most profitable good
	std::vector<unsigned int> mostProfitableJobIds;
	for(int jobId = 0; jobId < this->simulation.jobs.size(); jobId++){
		if(this->simulation.jobs[jobId].outputs[mostProfitableGoodId].second > 0){
			mostProfitableJobIds.push_back(jobId);
		}
	}

	// Execute smart job changing
	for(Agent &agent : this->simulation.agents){
		if(agent.satisfaction < SATISFACTION_THRESHOLD){
			// Change job
			agent.jobId = mostProfitableJobIds.back();
		}
	}
}
