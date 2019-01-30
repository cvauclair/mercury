#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <array>

#include "definitions.h"

// Number of goods in the simulation
static const unsigned int MAX_GOODS = 6;

// Names of the goods in the simulation with
// The ID of a good is its index in that array (the names of the goods
// are really only relevant to us humans, therefore they are stored in
// this global array and not inside the actual simulation). The agents
// only need to know that multiple goods exist, and that a good with a
// certain id has a certain price (more or less).
static const std::array<std::string, MAX_GOODS> goods = {
	"Wood",
	"Food",
	"Tool",
	"IronOre",
	"Coal",
	"Iron",
};

// The "jobs" or "recipes" of the simulation
// Each is a pair of arrays of size MAX_GOODS representing the inputs
// and outputs of the "job", as well as a string indicating the name of the job.
// E.g.: Producing iron requires 5 units of iron ore and 3 units of coal,
// which will yield 4 units of iron. That "job" would be represented
// by the following pair of arrays based on the good names above:
//		{0, 0, 0, 5, 3, 0}		// 5 Iron Ore and 3 Coal
//		{0, 0, 0, 0, 0, 4}		// 4 Iron
// Note: The value of these arrays only need to be the minimum integer
// factors since the whole array can be multiplies by the actual number of
// goods that the agent has, hence the use of char (1 byte) to represent the
// quantities of goods.

// Job definitions, again with the ID of a job being its index int the list
static const std::vector<Job<MAX_GOODS>> jobs = {
	{	// Wood cutting: 1 Tool -> 4 Wood
		"Wood Cutter", {0,0,1,0,0,0}, {4,0,0,0,0,0}
	},
	{	// Agriculture: 1 Tool -> 10 Food
		"Farmer", {0,0,1,0,0,0}, {0,10,0,0,0,0}
	},
	{	// Blacksmith: 1 Wood + 2 Iron -> 1 Tool
		"Toolmaker", {1,0,0,0,0,2}, {0,0,1,0,0,0}
	},
	{	// Iron ore mining: 1 Tool -> 5 Iron Ore
		"Iron Miner", {0,0,1,0,0,0}, {0,0,0,5,0,0}
	},
	{	// Coal ore mining: 1 Tool -> 5 Coal
		"Coal Miner", {0,0,1,0,0,0}, {0,0,0,0,5,0}
	},
	{	// Iron Smelting: 2 Iron Ore + 1 Coal -> 4 Iron
		"Iron Smelter", {0,0,0,2,1,0}, {0,0,0,0,0,4}
	}
};

// Agent consumption
// Similiarly to the above, this array represents the daily consumption
// (in food and/or goods) of each agent which is not related to their production.
// We reasonably assume that all agents share the same daily consumption (e.g.: all agents
// have equal metabolism) which greatly reduces memory usage and for the time being,
// doesn't critically impact the complexity of the simulation).
static const std::array<char, MAX_GOODS> consumption = {0,1,0,0,0,0};

// Price change factor
// How much the agents will adjust their offer prices by if the offers are unfulfilled
static const float PRICE_CHANGE_FACTOR = 0.05;

// Job change satisfaction threshold
// Represents under what satisfaction threshold the agent will change job
static const float SATISFACTION_THRESHOLD = 0.1;

#endif
