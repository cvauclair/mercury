#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <vector>
#include <stdio.h>

#include "config.h"

// Structure holding statistics for each day
struct DayStats{
	// Market offer stats
	unsigned int asksNb[MAX_GOODS] = {0};
	unsigned int bidsNb[MAX_GOODS] = {0};
	unsigned int fulfilledAsksNb[MAX_GOODS] = {0};
	unsigned int fulfilledBidsNb[MAX_GOODS] = {0};

	// Goods stats
	unsigned int quantityConsumed[MAX_GOODS] = {0};
	unsigned int quantityProduced[MAX_GOODS] = {0};
	unsigned int quantityTraded[MAX_GOODS] = {0};

	// Price stats
	float moneyTraded[MAX_GOODS] = {0};
	float averagePrice[MAX_GOODS] = {0};
};

// Internal class of the simulation that collects stats for viewing
class StatsManager{
	public:
		StatsManager();
		~StatsManager();

		// Export data to file (csv format)
		void exportStats(const std::string &filename);

		// Initializes the stats data array
		void init(unsigned int days);

		// Get the stats data struct of a day
		DayStats *getDayStats(int day);

		// Set/get sampling interval
		unsigned int getSamplingInterval();
		void setSamplingInterval(unsigned int interval);

		// Print in nice format to console
		void print(unsigned int day);

	private:
		unsigned int samplingInterval = 5;	// Number of days between samples
		std::vector<DayStats> stats;
};

#endif
