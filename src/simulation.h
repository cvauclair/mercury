#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "definitions.h"
#include "config.h"

// Simulation state
struct Simulation{
	// Agents
	std::vector<Agent<MAX_GOODS>> agents;

	// Market
	std::array<std::vector<Offer>, MAX_GOODS> asks;
	std::array<std::vector<Offer>, MAX_GOODS> bids;
	std::array<unsigned int, MAX_GOODS> quantityConsumed;
	std::array<unsigned int, MAX_GOODS> quantityProduced;
	std::array<unsigned int, MAX_GOODS> quantityTraded;
	std::array<float, MAX_GOODS> moneyTraded;
};

#endif
