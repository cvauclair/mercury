#include "statsmanager.h"

StatsManager::StatsManager()
{

}

StatsManager::~StatsManager()
{

}

void StatsManager::exportStats(const std::string &filename)
{
	// Open file
	std::ofstream file;
	file.open(filename);

	unsigned int goodId = 0;	// Init variable for reuse in loops
	unsigned int jobId = 0;

	// Write column labels

	// Write day label
	file << "day,";

	// Write total supply labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "supply,";
	}

	// Write asks and bids labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "asks,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "bids,";
	}

	// Write fulfilled asks and bids labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "fulfilledasks,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "fulfilledbids,";
	}

	// Write qty consumed, produced and traded labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "qtyconsumed,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "qtyproduced,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "qtytraded,";
	}

	// Write money traded and average price labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "moneytraded,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "avgprice,";
	}

	// Write job stat labels
	for(jobId = 0; jobId < jobs.size(); jobId++){
		file << "job" << jobId << ",";
	}
	for(jobId = 0; jobId < jobs.size(); jobId++){
		file << "job" << jobId << "sat,";
	}
	for(jobId = 0; jobId < jobs.size(); jobId++){
		file << "job" << jobId << "bal,";
	}

	// Newline
	file << std::endl;

	// Write actual data
	for(unsigned int day = 0; day < stats.size(); day++){
		// Write day
		file << day << ",";

		// Write total supply labels
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].totalSupply[goodId] << ",";
		}

		// Write asks and bids
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].asksNb[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].bidsNb[goodId] << ",";
		}

		// Write fulfilled asks and bids
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].fulfilledAsksNb[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].fulfilledBidsNb[goodId] << ",";
		}

		// Write qty consumed, produced and traded
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].quantityConsumed[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].quantityProduced[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].quantityTraded[goodId] << ",";
		}

		// Write money traded and average price
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].moneyTraded[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].averagePrice[goodId] << ",";
		}

		// Write agent stats
		// Write agent job distribution
		for(jobId = 0; jobId < jobs.size(); jobId++){
			file << this->stats[day].jobDistribution[jobId] << ",";
		}

		// Write agent average stats per job
		for(jobId = 0; jobId < jobs.size(); jobId++){
			file << this->stats[day].averageSatisfaction[jobId] << ",";
		}
		for(jobId = 0; jobId < jobs.size(); jobId++){
			file << this->stats[day].averageBalance[jobId] << ",";
		}

		// Newline
		file << std::endl;
	}

	file.close();
}

void StatsManager::compileDailyStats(Simulation &simulation)
{
	// Init new day stats
	DayStats<MAX_GOODS> dayStats;

	// Compile goods stats
	getAsksNb(simulation, dayStats);
	getBidsNb(simulation, dayStats);
	getFulfilledAsksNb(simulation, dayStats);
	getFulfilledBidsNb(simulation, dayStats);
	getTotalSupply(simulation, dayStats);
	getQuantityConsumed(simulation, dayStats);
	getQuantityProduced(simulation, dayStats);
	getQuantityTraded(simulation, dayStats);
	getMoneyTraded(simulation, dayStats);
	getAveragePrice(simulation, dayStats);

	// Compile agent stats
	getJobDistribution(simulation, dayStats);
	getAverageSatisfaction(simulation, dayStats);
	getAverageBalance(simulation, dayStats);

	// Add the newly compiled stats to the database
	this->stats.push_back(dayStats);
}

void StatsManager::getAsksNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get number of asks for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.asksNb[goodId] = simulation.asks[goodId].size();
	}
}

void StatsManager::getBidsNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get number of bids for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.bidsNb[goodId] = simulation.bids[goodId].size();
	}
}

void StatsManager::getFulfilledAsksNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get number of fulfilled asks for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.fulfilledAsksNb[goodId] = std::count_if(simulation.asks[goodId].begin(), simulation.asks[goodId].end(), [](Offer &ask){return ask.fulfilled;});
	}
}

void StatsManager::getFulfilledBidsNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get number of fulfilled bids for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.fulfilledBidsNb[goodId] = std::count_if(simulation.bids[goodId].begin(), simulation.bids[goodId].end(), [](Offer &bid){return bid.fulfilled;});
	}
}

void StatsManager::getTotalSupply(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get total supply available for each good type
	unsigned int totalSupply = 0;
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		totalSupply = 0;
		for(Agent<MAX_GOODS> &agent : simulation.agents){
			totalSupply += agent.stockpile[goodId];
		}
		dayStats.totalSupply[goodId] = totalSupply;
	}
}

void StatsManager::getQuantityConsumed(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get quantity consumed for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.quantityConsumed[goodId] = simulation.quantityConsumed[goodId];
	}
}

void StatsManager::getQuantityProduced(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get quantity produced for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.quantityProduced[goodId] = simulation.quantityProduced[goodId];
	}
}

void StatsManager::getQuantityTraded(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get quantity traded for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.quantityTraded[goodId] = simulation.quantityTraded[goodId];
	}
}

void StatsManager::getMoneyTraded(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get money traded for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		dayStats.moneyTraded[goodId] = simulation.moneyTraded[goodId];
	}
}

void StatsManager::getAveragePrice(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	// Get average price of goods sold/bought for each good type
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		if(simulation.quantityTraded[goodId] != 0){
			dayStats.averagePrice[goodId] = simulation.moneyTraded[goodId]/simulation.quantityTraded[goodId];
		}else{
			// If no good was traded, try to get last average price
			if(this->stats.size() > 0){
				dayStats.averagePrice[goodId] = this->stats.back().averagePrice[goodId];
			}else{
				dayStats.averagePrice[goodId] = 0;
			}
		}
	}
}

void StatsManager::getJobDistribution(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	for(Agent<MAX_GOODS> &agent : simulation.agents) {
		dayStats.jobDistribution[agent.jobId]++;
	}
}

void StatsManager::getAverageSatisfaction(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	std::array<float, 6> totalSatisfaction;
	for(Agent<MAX_GOODS> &agent : simulation.agents) {
		totalSatisfaction[agent.jobId] += agent.satisfaction;
	}

	// Divide by number of agents per job
	for(unsigned int i = 0; i < totalSatisfaction.size(); i++){
		dayStats.averageSatisfaction[i] = totalSatisfaction[i]/dayStats.jobDistribution[i];
	}
}

void StatsManager::getAverageBalance(Simulation &simulation, DayStats<MAX_GOODS> &dayStats)
{
	std::array<float, 6> totalBalance;
	for(Agent<MAX_GOODS> &agent : simulation.agents) {
		totalBalance[agent.jobId] += agent.balance;
	}

	// Divide by number of agents per job
	for(unsigned int i = 0; i < totalBalance.size(); i++){
		dayStats.averageBalance[i] = totalBalance[i]/dayStats.jobDistribution[i];
	}
}

DayStats<MAX_GOODS> *StatsManager::getDayStats(int day)
{
	if(day < 0){
		return &this->stats[0];
	}else{
		return &this->stats[day];
	}
}

unsigned int StatsManager::getSamplingInterval()
{
	return samplingInterval;
}

void StatsManager::setSamplingInterval(unsigned int interval)
{
	samplingInterval = interval;
}

void StatsManager::print(unsigned int day)
{
	DayStats<MAX_GOODS> *ds = &this->stats[day];
	printf("[Day %d]\n", day + 1);
	printf("Good\tAsks\tBids\tFulfilled Asks (%)\tFulfilled Bids (%)\tMoney Traded\tAverage Price\n");
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		printf("%s", goods[goodId].data());	// Good name
		printf("\t%d", ds->asksNb[goodId]);	// Number of asks
		printf("\t%d", ds->bidsNb[goodId]);	// Number of bids
		printf("\t%d (%f)", ds->fulfilledAsksNb[goodId], (ds->asksNb[goodId] != 0 ? 100.0*ds->fulfilledAsksNb[goodId]/(float)ds->asksNb[goodId] : 0));	// Number of fulfilled asks
		printf("\t%d (%f)", ds->fulfilledBidsNb[goodId], (ds->bidsNb[goodId] != 0 ? 100.0*ds->fulfilledBidsNb[goodId]/(float)ds->bidsNb[goodId] : 0));	// Number of fulfilled bids
		printf("\t%f", ds->moneyTraded[goodId]);	// Value of goods traded
		printf("\t\t%f\n", ds->averagePrice[goodId]);	// Average price
	}
}

