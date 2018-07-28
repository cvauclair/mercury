#ifndef TESTCONFIG_H
#define TESTCONFIG_H

#include <vector>
#include <array>

#include "definitions.h"

namespace TEST{

// Number of goods in the simulation
static const unsigned int TEST::MAX_GOODS = 4;

static const std::array<std::string, TEST::MAX_GOODS> goods = {
	"Wood",
	"Food",
	"Tool",
	"Coal"
};

// Job definitions, again with the ID of a job being its index int the list
static const std::vector<Job<TEST::MAX_GOODS>> jobs = {
	{
		"Wood Cutter", {0,0,1,0}, {4,0,0,0}
	},
	{
		"Farmer", {0,0,1,0}, {0,10,0,0}
	},
	{
		"Iron Miner", {0,0,1,0}, {0,0,0,5}
	},
	{
		"Coal Miner", {0,0,1,0}, {0,0,0,5}
	},
};

// Agent consumption
static const std::array<char, TEST::MAX_GOODS> consumption = {3,0,0,0};

// Price change factor
// How much the agents will adjust their offer prices by if the offers are unfulfilled
static const float PRICE_CHANGE_FACTOR = 0.05;

// Job change satisfaction threshold
// Represents under what satisfaction threshold the agent will change job
static const float SATISFACTION_THRESHOLD = 0.1;

}

#endif
