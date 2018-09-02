#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>

#include "config.h"
#include "definitions.h"
#include "simulation.h"

// Class that collects data for viewing and analysis
class StatsManager{
	public:
		StatsManager();
		~StatsManager();

		// Export data to file (csv format)
		void exportStats(const std::string &filename);

		// Collect daily data from simulation
		void compileDailyStats(Simulation &simulation);

		// These methods split up the data compilation process and saves the data in dayStats
		void getAsksNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getBidsNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getFulfilledAsksNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getFulfilledBidsNb(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getTotalSupply(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getQuantityConsumed(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getQuantityProduced(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getQuantityTraded(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getMoneyTraded(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);
		void getAveragePrice(Simulation &simulation, DayStats<MAX_GOODS> &dayStats);

		// Get the stats data struct of a day
		DayStats<MAX_GOODS> *getDayStats(int day);

		// Set/get sampling interval
		unsigned int getSamplingInterval();
		void setSamplingInterval(unsigned int interval);

		// Print in nice format to console
		void print(unsigned int day);

	private:
		// Data
		unsigned int samplingInterval = 5;	// Number of days between samples
		std::vector<DayStats<MAX_GOODS>> stats;
};

#endif
