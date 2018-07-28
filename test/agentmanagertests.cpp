#include "catch.hpp"

#include <vector>

#include "agentmanager.h"

TEST_CASE("Agent manager buffer allocation", "[AGENT_MANAGER]"){
	unsigned int popSize = 2;
	unsigned int goodsNb = 4;

	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	// Calculate buffer size
	unsigned int balancesBufferSize = popSize * sizeof(float);
	unsigned int jobIdsBufferSize = popSize * sizeof(bool);
	unsigned int stockpilesBufferSize = popSize * goodsNb * sizeof(char);
	unsigned int satisfactionsBufferSize = popSize * sizeof(float);
	unsigned int offerPricesBufferSize = popSize * goodsNb * sizeof(float);
	unsigned int lastOfferFulfilledBufferSize = popSize * goodsNb * sizeof(bool);

	unsigned int desiredBufferSize = balancesBufferSize + jobIdsBufferSize +
			stockpilesBufferSize + satisfactionsBufferSize + offerPricesBufferSize + lastOfferFulfilledBufferSize;

	REQUIRE(agentManager->getBufferSize() == desiredBufferSize);

	delete agentManager;
}

TEST_CASE("Setting agent balance", "[AGENT_MANAGER]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 8;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	// Init balances
	std::vector<float> startingBalances = {0, 30, 4, 0, 10};
	for(int i = 0; i < popSize; i++){
		agentManager->setBalance(i, startingBalances[i]);
	}

	for(int i = 0; i < popSize; i++){
		CHECK(agentManager->getBalance(i) == startingBalances[i]);
	}

	delete agentManager;
}

TEST_CASE("Incrementing agent balance", "[AGENT_MANAGER]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 8;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	// Init balances
	std::vector<float> startingBalances = {12, 30, 4, 999, 10};
	for(int i = 0; i < popSize; i++){
		agentManager->setBalance(i, startingBalances[i]);
	}

	// Decrement balances
	for(int i = 0; i < popSize; i++){
		agentManager->incrementBalance(i, 2);
	}

	// Desired balances
	std::vector<float> desiredBalances = {14, 32, 6, 1001, 12};

	// Assert
	for(int i = 0; i < popSize; i++){
		CHECK(agentManager->getBalance(i) == desiredBalances[i]);
	}

	delete agentManager;
}

TEST_CASE("Decrementing agent balance", "[AGENT_MANAGER]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 8;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	// Init balances
	std::vector<float> startingBalances = {12, 30, 4, 999, 10};
	for(int i = 0; i < popSize; i++){
		agentManager->setBalance(i, startingBalances[i]);
	}

	// Decrement balances
	for(int i = 0; i < popSize; i++){
		agentManager->decrementBalance(i, 4);
	}

	// Desired balances
	std::vector<float> desiredBalances = {8, 26, 0, 995, 6};

	// Assert
	for(int i = 0; i < popSize; i++){
		CHECK(agentManager->getBalance(i) == desiredBalances[i]);
	}

	delete agentManager;
}

TEST_CASE("Modifying agent balance", "[AGENT_MANAGER]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 8;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	// Init balances
	std::vector<float> startingBalances = {12, 30, 4, 999, 10};
	for(int i = 0; i < popSize; i++){
		agentManager->setBalance(i, startingBalances[i]);
	}

	// Modify balance
	agentManager->getBalance(0) -= 4;

	// Desired balances
	std::vector<float> desiredBalances = {8, 30, 4, 999, 10};

	// Assert
	for(int i = 0; i < popSize; i++){
		CHECK(agentManager->getBalance(i) == desiredBalances[i]);
	}

	delete agentManager;
}

TEST_CASE("Set good stockpile quantity", "[AGENT_MANAGER]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 8;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	agentManager->setGoodStockpileQuantity(0,3,89);
	CHECK(agentManager->getGoodStockpileQuantity(0,3) == 89);

	delete agentManager;
}
