#include <array>
#include <vector>

#include "agentmanager.h"
#include "consumptionsystem.h"

#include "catch.hpp"

TEST_CASE("Executing consumption w/ sufficient goods", "[CONSUMPTION_SYSTEM]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 4;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	std::vector<char> consumption = {3,0,0,0};

	unsigned int agentId = 3;
	agentManager->setGoodStockpileQuantity(agentId, 0, 4);

	ConsumptionSystem::doConsumption(4, consumption, agentManager->getStockpile(agentId), agentManager->getSatisfaction(agentId));

	CHECK(agentManager->getGoodStockpileQuantity(agentId, 0) == 1);
	CHECK(agentManager->getSatisfaction(agentId) == 1.0);

	delete agentManager;
}

TEST_CASE("Executing consumption w/ partially sufficient goods", "[CONSUMPTION_SYSTEM]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 4;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	std::vector<char> consumption = {4,0,0,0};

	unsigned int agentId = 3;
	agentManager->setGoodStockpileQuantity(agentId, 0, 2);

	ConsumptionSystem::doConsumption(4, consumption, agentManager->getStockpile(agentId), agentManager->getSatisfaction(agentId));

	CHECK(agentManager->getGoodStockpileQuantity(agentId, 0) == 0);
	CHECK(agentManager->getSatisfaction(agentId) == 0.5);

	delete agentManager;
}

TEST_CASE("Executing consumption w/out goods", "[CONSUMPTION_SYSTEM]"){
	unsigned int popSize = 5;
	unsigned int goodsNb = 4;

	// Init database
	AgentManager *agentManager = new AgentManager();
	agentManager->init(popSize, goodsNb);

	std::vector<char> consumption = {3,0,0,0};

	unsigned int agentId = 3;
	agentManager->setGoodStockpileQuantity(agentId, 0, 0);

	ConsumptionSystem::doConsumption(4, consumption, agentManager->getStockpile(agentId), agentManager->getSatisfaction(agentId));

	CHECK(agentManager->getGoodStockpileQuantity(agentId, 0) == 0);
	CHECK(agentManager->getSatisfaction(agentId) == 0.0);

	delete agentManager;
}
