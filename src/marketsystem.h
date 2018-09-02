#ifndef MARKETSYSTEM_H
#define MARKETSYSTEM_H

#include "simulation.h"

class MarketSystem{
	public:
		static void generateOffers(Simulation &simulation);
		static void generateAsk(Simulation &simulation, unsigned int agentId, unsigned int goodId, float price, unsigned int quantity);
		static void generateBid(Simulation &simulation, unsigned int agentId, unsigned int goodId, float price, unsigned int quantity);
		static void resolveOffers(Simulation &simulation);

		// This method will be moved to the agent update phase later
		static float getPrice(Simulation &simulation, unsigned int agentId, unsigned int goodId, bool isSelling);
};

#endif
