#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <vector>

// Definitions of various data structures used throughout the simulation including entities and statistics collections

// Goods definition
struct Goods{
	Goods(unsigned int id, std::string key, std::string name): id(id), key(key), name(name) {}
	unsigned int id = 0;
	std::string key = "";
	std::string name = "";
};

// Job definition
struct Job{
	Job(){}
	Job(unsigned int id, std::string name): id(id), name(name) {}
	unsigned int id = 0;
	std::string key = "";
	std::string name = "";
	std::vector<std::pair<std::string, unsigned int>> inputs;
	std::vector<std::pair<std::string, unsigned int>> outputs;
};

// Agent definition
struct Agent{
	// Economic state
	float balance = 100.0;	// Starting funds
	unsigned int jobId = 0;
	std::vector<char> stockpile = {0};

	// "Mind" state
	float satisfaction = 1.0;	// [0,1]

	// Market feedback
	std::vector<float> offerPrice  = {1.0f};
//	bool lastOfferWasAsk[MAX_GOODS] = {true};		// Type of last offer
	std::vector<bool> lastOfferFulfilled = {false};	// Fulfillement of last offer
};

// Offer definition
struct Offer{
	Offer(unsigned int agentId, float price, unsigned int quantity): agentId(agentId), price(price), originalQuantity(quantity), quantity(quantity){}
	unsigned int agentId = 0;
	float price = 0.0;
	unsigned int originalQuantity = 0;
	unsigned int quantity = 0;
	bool fulfilled = false;
};

#endif
