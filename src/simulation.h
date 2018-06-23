#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "config.h"
#include "statsmanager.h"

// Simulation flow:
//	for each timestep
//		do agent consumption
//		do agent production
//		generate agent's market offers
//		resolve offers (via double auction system)
//		update agents' state (includes updating price of offers and changing job) <- The step where the machine learning will fit!
class Simulation{
	public:
		Simulation(unsigned int popSize);
		~Simulation();

		// Run the simulation for 'days' days (Note: day is only a word, it could be any timestep where a full cycle occurs)
		void run(unsigned int days);

		unsigned int getCurrentDay();

		StatsManager &getStatsManager();

	private:
		// Production & consumption methods
		void doProduction();
		void doConsumption();

		// Double auction methods
		void generateOffers();
		float getPrice(unsigned int agentId, unsigned int goodId, bool isSelling);
		void generateAsk(unsigned int agentId, unsigned int goodId, float price, unsigned int quantity);
		void generateBid(unsigned int agentId, unsigned int goodId, float price, unsigned int quantity);
		void resolveOffers();

		// Agent feedback methods
		void updateAgents();

		// Daily misc methods
		void compileDailyStats();

		// Data
		unsigned int currentDay = 0;

		std::vector<Agent> agents;
		std::array<std::vector<Offer>, MAX_GOODS> asks;
		std::array<std::vector<Offer>, MAX_GOODS> bids;

		StatsManager statsManager;
		DayStats *dayStats = nullptr;
};

#endif
