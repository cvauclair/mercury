#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Number of goods in the simulation
static const unsigned int MAX_GOODS = 6;

// Agent definition
struct Agent{
	// Economic state
	float balance = 100.0;	// Starting funds
	unsigned int jobId = 0;
	char stockpile[MAX_GOODS] = {0};

	// "Mind" state
	float satisfaction = 1.0;	// [0,1]

	// Market feedback
	float offerPrice[MAX_GOODS] = {1.0};		// Last price he offered (ask or bid) for each good
//	bool lastOfferWasAsk[MAX_GOODS] = {true};		// Type of last offer
	bool lastOfferFulfilled[MAX_GOODS] = {false};	// Fulfillement of last offer
};

// Offer definition
struct Offer{
	unsigned int agentId = 0;
	float price = 0.0;
	unsigned int quantity = 0;
	bool fulfilled = false;
};

// Job definition
struct Job{
	char *name = nullptr;
	char inputs[MAX_GOODS] = {0};
	char ouputs[MAX_GOODS] = {0};
};

#endif
