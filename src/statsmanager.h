#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <vector>
#include <stdio.h>
#include <fstream>

#include "config.h"

// Class that collects data for viewing and analysis
class StatsManager{
	public:
		StatsManager();
		~StatsManager();

		// Export data to file (csv format)
		void exportStats(const std::string &filename);

		// Initializes the stats data array
		void init(unsigned int days);

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
