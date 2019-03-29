#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>

#include "definitions.h"

// Agent consumption
// Similiarly to the above, this array represents the daily consumption
// (in food and/or goods) of each agent which is not related to their production.
// We reasonably assume that all agents share the same daily consumption (e.g.: all agents
// have equal metabolism) which greatly reduces memory usage and for the time being,
// doesn't critically impact the complexity of the simulation).
static const std::vector<char> consumption = {0,1,0,0,0,0};

// Price change factor
// How much the agents will adjust their offer prices by if the offers are unfulfilled
static const float PRICE_CHANGE_FACTOR = 0.05;

// Job change satisfaction threshold
// Represents under what satisfaction threshold the agent will change job
static const float SATISFACTION_THRESHOLD = 0.1;

// Simulation state
struct Simulation{
	// Config
	std::vector<Goods> goods;
	std::unordered_map<std::string, unsigned int> goodsIds;

	std::vector<Job> jobs;
	std::unordered_map<std::string, unsigned int> jobsIds;

	// Agents
	std::vector<Agent> agents;

	// Market
	std::vector<std::vector<Offer>> bids;
	std::vector<std::vector<Offer>> asks;

	std::vector<unsigned int> quantityConsumed;
	std::vector<unsigned int> quantityProduced;
	std::vector<unsigned int> quantityTraded;
	std::vector<float> moneyTraded;
};

#endif
