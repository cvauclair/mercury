#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "config.h"
#include "statsmanager.h"

#include "consumptionsystem.h"
#include "productionsystem.h"

#include "agentmanager.h"

// Simulation flow:
//	for each timestep
//		do agent consumption
//		do agent production
//		generate agent's market offers
//		resolve offers (via double auction system)
//		update agents' state (includes updating price of offers and changing job) <- The step where the machine learning will fit!
class Simulation{
	public:
		Simulation(unsigned int popSize, unsigned int goodsNb);
		~Simulation();

		// Run the simulation for 'days' days (Note: day is only a word, it could be any timestep where a full cycle occurs)
		void run(unsigned int days);

		unsigned int getCurrentDay();

		StatsManager &getStatsManager();

	private:
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

		// Simulation databases
		AgentManager agentManager;

		std::vector<Agent<MAX_GOODS>> agents;
		std::array<std::vector<Offer>, MAX_GOODS> asks;
		std::array<std::vector<Offer>, MAX_GOODS> bids;

		// Data collection
		StatsManager statsManager;
		DayStats<MAX_GOODS> *dayStats = nullptr;
};

#endif
