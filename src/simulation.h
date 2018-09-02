#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "config.h"

// Simulation flow:
//	for each timestep
//		do agent consumption
//		do agent production
//		generate agent's market offers
//		resolve offers (via double auction system)
//		update agents' state (includes updating price of offers and changing job) <- The step where the machine learning will fit!

struct Simulation{
	// Simulation state
	std::vector<Agent<MAX_GOODS>> agents;
	std::array<std::vector<Offer>, MAX_GOODS> asks;
	std::array<std::vector<Offer>, MAX_GOODS> bids;
	std::array<unsigned int, MAX_GOODS> quantityConsumed;
	std::array<unsigned int, MAX_GOODS> quantityProduced;
	std::array<unsigned int, MAX_GOODS> quantityTraded;
	std::array<float, MAX_GOODS> moneyTraded;

	public:
		Simulation();
		Simulation(unsigned int popSize, unsigned int goodsNb);
		~Simulation();

		unsigned int getCurrentDay();

	private:
		void resolveOffers();

		// Data
		unsigned int currentDay = 0;
};

#endif
