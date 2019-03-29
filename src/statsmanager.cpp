#include "statsmanager.h"

StatsManager::StatsManager()
{

}

StatsManager::StatsManager(StatsManager &statManager)
{
	// Copy ctor
}

StatsManager::~StatsManager()
{

}

void StatsManager::setGoodsIds(std::unordered_map<std::string, unsigned int> &goodsIds)
{
	this->goodsIds = goodsIds;
}

void StatsManager::setJobsIds(std::unordered_map<std::string, unsigned int> &jobsIds)
{
	this->jobsIds = jobsIds;
}

void StatsManager::exportStats(const std::string &filename)
{
	// Open file
	std::ofstream file;
	file.open(filename);

	// Write labels
	file << "DAY,";
	for(std::string goodsStatLabel: goodsStatLabels){
		for(auto [key, id]: this->goodsIds){
			file << key << "_" << goodsStatLabel << ",";
		}
	}
	for(std::string jobStatLabel: jobStatLabels){
		for(auto [key, id]: this->jobsIds){
			file << key << "_" << jobStatLabel << ",";
		}
	}
	file << std::endl;

	// Write data
	for(DayStats &dayStats: this->stats){
		file << StatsManager::printDayStats(dayStats) << std::endl;
	}

	file.close();
}

std::string StatsManager::printDayStats(DayStats &dayStats)
{
	std::stringstream ss;
	ss << dayStats.day << ",";

	// Goods stats
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.numAsks << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.numBids << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.numFulfilledAsks << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.numFulfilledBids << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.quantityProduced << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.quantityConsumed << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.quantityTraded << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.totalSupply << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.moneyTraded << ",";
	}
	for(GoodsStats &goodStats: dayStats.goodsStats){
		ss << goodStats.averagePrice << ",";
	}

	// Jobs stats
	for(JobStats &jobStats: dayStats.jobsStats){
		ss << jobStats.numAgents << ",";
	}
	for(JobStats &jobStats: dayStats.jobsStats){
		ss << jobStats.averageSatisfaction << ",";
	}
	for(JobStats &jobStats: dayStats.jobsStats){
		ss << jobStats.averageBalance << ",";
	}

	return ss.str();
}

void StatsManager::recordStats(Simulation &simulation)
{
	this->stats.emplace_back(this->stats.size() + 1, StatsManager::compileGoodsStats(simulation), StatsManager::compileJobsStats(simulation));
}

std::vector<GoodsStats> StatsManager::compileGoodsStats(Simulation &simulation)
{
	// Init good stats
	std::vector<GoodsStats> goodsStats(simulation.goods.size());

	for(unsigned int i = 0, goodsId = simulation.goodsIds[simulation.goods[i].key]; i < simulation.goods.size(); i++){
		// Bid ask stats
		goodsStats[goodsId].numAsks = simulation.asks[goodsId].size();
		goodsStats[goodsId].numBids = simulation.bids[goodsId].size();
		goodsStats[goodsId].numFulfilledAsks = std::count_if(simulation.asks[goodsId].begin(), simulation.asks[goodsId].end(), [](Offer &ask){return ask.fulfilled;});
		goodsStats[goodsId].numFulfilledBids = std::count_if(simulation.bids[goodsId].begin(), simulation.bids[goodsId].end(), [](Offer &bid){return bid.fulfilled;});

		// Activity stats
		goodsStats[goodsId].quantityProduced = simulation.quantityProduced[goodsId];
		goodsStats[goodsId].quantityConsumed = simulation.quantityConsumed[goodsId];
		goodsStats[goodsId].quantityTraded = simulation.quantityTraded[goodsId];

		// Money stats
		goodsStats[goodsId].moneyTraded = simulation.moneyTraded[goodsId];

		// Average price

		// Get average price of goods sold/bought for each good type
		if(simulation.quantityTraded[goodsId] != 0){
			goodsStats[goodsId].averagePrice = simulation.moneyTraded[goodsId]/simulation.quantityTraded[goodsId];
		}else{
			// If no good was traded, try to get last average price
//			if(this->stats.size() > 0){
//				dayStats.averagePrice[goodId] = this->stats.back().averagePrice[goodId];
//			}else{
//				dayStats.averagePrice[goodId] = 0;
//			}
		}

	}

	// Supply stats
	for(Agent &agent : simulation.agents){
		for(unsigned int i = 0, goodsId = simulation.goodsIds[simulation.goods[i].key]; i < simulation.goods.size(); i++){
			goodsStats[goodsId].totalSupply += agent.stockpile[goodsId];
		}
	}

	return goodsStats;
}

std::vector<JobStats> StatsManager::compileJobsStats(Simulation &simulation)
{
	std::vector<JobStats> jobsStats(simulation.jobs.size());

	// Number of workers
	for(Agent &agent: simulation.agents){
		jobsStats[agent.jobId].numAgents++;
	}

	// Average satisfaction and balance
	std::vector<float> totalSatisfaction(simulation.jobs.size());
	std::vector<float> totalBalance(simulation.jobs.size());
	for(Agent &agent : simulation.agents) {
		totalSatisfaction[agent.jobId] += agent.satisfaction;
		totalBalance[agent.jobId] += agent.balance;
	}

	// Divide by number of agents per job
	for(unsigned int i = 0; i < totalSatisfaction.size(); i++){
		jobsStats[i].averageSatisfaction = totalSatisfaction[i]/jobsStats[i].numAgents;
		jobsStats[i].averageBalance = totalBalance[i]/jobsStats[i].numAgents;
	}

	return jobsStats;
}

std::vector<unsigned int> StatsManager::getNumAsks(std::string goodsKey)
{
	std::vector<unsigned int> numAsks(this->stats.size());
	for(DayStats &dayStats: this->stats){
		numAsks.push_back(dayStats.goodsStats[this->goodsIds[goodsKey]].numAsks);
	}
	return numAsks;
}

std::vector<unsigned int> StatsManager::getNumBids(std::string goodsKey)
{
	std::vector<unsigned int> numBids(this->stats.size());
	for(DayStats &dayStats: this->stats){
		numBids.push_back(dayStats.goodsStats[this->goodsIds[goodsKey]].numBids);
	}
	return numBids;
}

void StatsManager::getAveragePrice(Simulation &simulation, DayStats &dayStats)
{
	// Get average price of goods sold/bought for each good type
//	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
//		if(simulation.quantityTraded[goodId] != 0){
//			dayStats.averagePrice[goodId] = simulation.moneyTraded[goodId]/simulation.quantityTraded[goodId];
//		}else{
//			// If no good was traded, try to get last average price
//			if(this->stats.size() > 0){
//				dayStats.averagePrice[goodId] = this->stats.back().averagePrice[goodId];
//			}else{
//				dayStats.averagePrice[goodId] = 0;
//			}
//		}
//	}
}

DayStats *StatsManager::getDayStats(int day)
{
	if(day < 0){
		return &this->stats[0];
	}else{
		return &this->stats[day];
	}
}

DayStats StatsManager::getLastDayStats()
{
	if(this->stats.empty()){
		throw std::out_of_range("Stats is empty!");
	}else{
		return this->stats.back();
	}
}

unsigned int StatsManager::getMostProfitableGood()
{
	unsigned int mostProfitableGoodId = 0;
//	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
//		if(this->getLastDayStats().averagePrice[goodId] > this->getLastDayStats().averagePrice[mostProfitableGoodId]){
//			mostProfitableGoodId = goodId;
//		}
//	}

	return mostProfitableGoodId;
}

unsigned int StatsManager::getSamplingInterval()
{
	return samplingInterval;
}

void StatsManager::setSamplingInterval(unsigned int interval)
{
	samplingInterval = interval;
}
