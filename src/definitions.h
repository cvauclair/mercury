#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Definitions of various data structures used throughout the simulation including entities and statistics collections

// Agent definition
template<unsigned int MAX_GOODS>
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
template<unsigned int MAX_GOODS>
struct Job{
	char *name = nullptr;
	char inputs[MAX_GOODS] = {0};
	char ouputs[MAX_GOODS] = {0};
};

// Structure holding statistics for each day (or timestep)
template<unsigned int MAX_GOODS>
struct DayStats{
	// Market offer stats
	unsigned int asksNb[MAX_GOODS] = {0};
	unsigned int bidsNb[MAX_GOODS] = {0};
	unsigned int fulfilledAsksNb[MAX_GOODS] = {0};
	unsigned int fulfilledBidsNb[MAX_GOODS] = {0};

	// Goods stats
	unsigned int quantityConsumed[MAX_GOODS] = {0};
	unsigned int quantityProduced[MAX_GOODS] = {0};
	unsigned int quantityTraded[MAX_GOODS] = {0};
	unsigned int totalSupply[MAX_GOODS] = {0};

	// Price stats
	float moneyTraded[MAX_GOODS] = {0};
	float averagePrice[MAX_GOODS] = {0};
};

#endif
