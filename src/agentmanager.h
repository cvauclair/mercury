#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include "stdlib.h"
#include "string.h"

// Low level interface that manages agents data in an ECS architecture inspired way (for performance).
// Although not explicitely defined, the manager implements the following structure.
//	struct Agent{
//		// Economic state
//		float balance = 100.0;	// Starting funds
//		unsigned int jobId = 0;
//		char stockpile[MAX_GOODS] = {0};

//		// "Mind" state
//		float satisfaction = 1.0;	// [0,1]

//		// Market feedback
//		float offerPrice[MAX_GOODS] = {1.0};		// Last price he offered (ask or bid) for each good
//		bool lastOfferFulfilled[MAX_GOODS] = {false};	// Fulfillement of last offer
//	};
// Important: For performance reasons (these methods are designed to be called very often),
// the class does not check if the supplied IDs are valid. This should be done at a higher level
class AgentManager{
	public:
		AgentManager();
		~AgentManager();

		// Params getters
		unsigned int getPopSize() const {return this->popSize;}
		unsigned int getGoodsNb() const {return this->goodsNb;}

		// Utility methods
		void init(unsigned int popSize, unsigned int goodsNb);
		unsigned int getBufferSize(){return this->bufferSize;}

		// Balances
		void setBalance(unsigned int agentId, float balance);
		void incrementBalance(unsigned int agentId, float increment);
		void decrementBalance(unsigned int agentId, float decrement);
		float &getBalance(unsigned int agentId);

		// JobIds
		void setJobId(unsigned int agentId, unsigned int jobId);
		unsigned int &getJobId(unsigned int agentId);

		// Stockpiles
		void setGoodStockpileQuantity(unsigned int agentId, unsigned int goodId, char quantity);
		void incrementGoodStockpileQuantity(unsigned int agentId, unsigned int goodId, char increment);
		void decrementGoodStockpileQuantity(unsigned int agentId, unsigned int goodId, char decrement);
		char &getGoodStockpileQuantity(unsigned int agentId, unsigned int goodId);
		char *getStockpile(unsigned int agentId);

		// Satisfaction
		void setSatisfaction(unsigned int agentId, float satisfaction);
		float &getSatisfaction(unsigned int agentId);

		// Offer prices
		void setGoodOfferPrice(unsigned int agentId, unsigned int goodId, float price);
		void incrementGoodOfferPrice(unsigned int agentId, unsigned int goodId, float increment);
		void decrementGoodOfferPrice(unsigned int agentId, unsigned int goodId, float decrement);
		float &getGoodOfferPrice(unsigned int agentId, unsigned int goodId);
		float *getOfferPrices(unsigned int agentId);

		// Last offer fulfilled
		void setGoodLastOfferFulfilled(unsigned int agentId, unsigned int goodId, bool fulfilled);
		bool &getGoodLastOfferFulfilled(unsigned int agentId, unsigned int goodId);

	private:
		// Database parameters
		unsigned int popSize = 0;
		unsigned int goodsNb = 0;

		// Raw buffer
		unsigned int bufferSize = 0;
		void *buffer = nullptr;

		// Member ptrs
		float *balancesPtr = nullptr;
		unsigned int *jobIdsPtr = nullptr;
		char *stockpilesPtr = nullptr;
		float *satifactionsPtr = nullptr;
		float *offerPricesPtr = nullptr;
		bool *lastOfferFulfilledPtr = nullptr;
};

#endif
