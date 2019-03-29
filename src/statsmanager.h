#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "definitions.h"
#include "simulation.h"
//#include "simulationframe.h"
#include "statistics.h"

static const std::vector<std::string> goodsStatLabels = {
	"SUPPLY",
	"ASKS",
	"BIDS",
	"FULFILLED_ASKS",
	"FULFILLED_BIDS",
	"QTY_PRODUCED",
	"QTY_CONSUMED",
	"QTY_TRADED",
	"MONEY_TRADED",
	"AVG_PRICE"
};

static const std::vector<std::string> jobStatLabels = {
	"NUM_WORKERS",
	"AVG_SATISFACTION",
	"AVG_BALANCE"
};

// Class that collects data for viewing and analysis
class StatsManager{
	public:
		StatsManager();
		StatsManager(StatsManager &statManager);
		~StatsManager();

		void setGoodsIds(std::unordered_map<std::string, unsigned int> &goodsIds);
		void setJobsIds(std::unordered_map<std::string, unsigned int> &jobsIds);

		// Use of simulation to compile the stats
		void recordStats(Simulation &simulation);
		static std::vector<GoodsStats> compileGoodsStats(Simulation &simulation);
		static std::vector<JobStats> compileJobsStats(Simulation &simulation);

		// Export data to file (csv format)
		void exportStats(const std::string &filename);
		static std::string printDayStats(DayStats &dayStats);

		// Get stats series
		std::vector<unsigned int> getNumAsks(std::string goodsKey);
		std::vector<unsigned int> getNumBids(std::string goodsKey);












		// These methods split up the data compilation process and saves the data in dayStats
		// Goods stats methods
		void getAveragePrice(Simulation &simulation, DayStats &dayStats);

		// Get the stats data struct of a day
		DayStats *getDayStats(int day);
		DayStats getLastDayStats();

		// Get some stats
		unsigned int getMostProfitableGood();

		// Set/get sampling interval
		unsigned int getSamplingInterval();
		void setSamplingInterval(unsigned int interval);

	private:
		// Data
		unsigned int samplingInterval = 5;	// Number of days between samples
		std::vector<DayStats> stats;

		// Maintain a copy of good id and job id maps
		std::unordered_map<std::string, unsigned int> goodsIds;
		std::unordered_map<std::string, unsigned int> jobsIds;
};

#endif
