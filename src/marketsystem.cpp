#include "marketsystem.h"

void MarketSystem::generateOffers(Simulation &simulation)
{
	// Variables
	int needs[MAX_GOODS] = {0};
	unsigned int totalNeeds = 0;

	unsigned int popSize = simulation.agents.size();
	for(unsigned int agentId = 0; agentId < popSize; agentId++){
		// Reset variables
		for(int goodId = 0; goodId < MAX_GOODS; goodId++) {needs[goodId] = 0;}

		// Get all needs (negative need is a surplus to be sold)
		for(int goodId = 0; goodId < MAX_GOODS; goodId++){
			needs[goodId] = 2 * (jobs[simulation.agents[agentId].jobId].inputs[goodId] + consumption[goodId]) - simulation.agents[agentId].stockpile[goodId];

			// Add to total positive needs if positive
			if(needs[goodId] > 0){
				totalNeeds += needs[goodId];
			}
		}

		// Set bids prices


		// Generate offers (agents will ask for twice their needs)
		for(unsigned int i = 0; i < MAX_GOODS; i++){
			if(needs[i] > 0){
				MarketSystem::generateBid(simulation, agentId, i, MarketSystem::getPrice(simulation, agentId, i, false), needs[i]);
			}else if(needs[i] < 0){
				MarketSystem::generateAsk(simulation, agentId, i, MarketSystem::getPrice(simulation, agentId, i, true), -1 * needs[i]);
			}

		}
	}
}

void MarketSystem::generateAsk(Simulation &simulation, unsigned int agentId, unsigned int goodId, float price, unsigned int quantity)
{
	simulation.asks[goodId].push_back({agentId, price, quantity, false});
}

void MarketSystem::generateBid(Simulation &simulation, unsigned int agentId, unsigned int goodId, float price, unsigned int quantity)
{
	simulation.bids[goodId].push_back({agentId, price, quantity, false});
}

void MarketSystem::resolveOffers(Simulation &simulation)
{
	// Temporary variables
	unsigned int quantityTraded = 0;
	float clearingPrice = 0;
	float money = 0;
	std::vector<Offer>::iterator ask;
	std::vector<Offer>::iterator bid;

	// For each good
	for(unsigned int goodId = 0; goodId < MAX_GOODS; goodId++){
		// Sort asks and in increasing order of prices and bids in decreasing order
		std::sort(simulation.asks[goodId].begin(), simulation.asks[goodId].end(), [](Offer &ask1, Offer &ask2){return ask1.price < ask2.price;});
		std::sort(simulation.bids[goodId].begin(), simulation.bids[goodId].end(), [](Offer &bid1, Offer &bid2){return bid1.price > bid2.price;});

		// Init iterators
		ask = simulation.asks[goodId].begin();
		bid = simulation.bids[goodId].begin();

		// Resolve offers
		while(ask != simulation.asks[goodId].end() & bid != simulation.bids[goodId].end()){
			// Go to next bid if the bidder cannot afford to buy (works since asks (i.e.: seller offers) are ordered by price)
			if((*bid).price < (*ask).price){
				(*bid).fulfilled = false;
				std::advance(bid, 1);
				continue;
			}

			// Get quantity that will trade hands
			quantityTraded = std::min((*bid).quantity, (*ask).quantity);

			// Get price of transaction
			clearingPrice = (*ask).price;

			// Execute transaction
			if(quantityTraded > 0){
				// Update offers
				(*ask).quantity -= quantityTraded;
				(*bid).quantity -= quantityTraded;
//				std::cout << "Offer resolved: " << quantityTraded << " goods traded for " << clearingPrice << "$/unit" << std::endl;

				// Transfer quantityTraded of good from seller agent to buyer agent
				simulation.agents[(*ask).agentId].stockpile[goodId] -= quantityTraded;
				simulation.agents[(*bid).agentId].stockpile[goodId] += quantityTraded;

				// Transfer clearingPrice * quantityTraded money from buyer agent to seller agent
				money = clearingPrice * quantityTraded;
				simulation.agents[(*ask).agentId].balance += money;
				simulation.agents[(*bid).agentId].balance -= money;

				// Collect data
				simulation.quantityTraded[goodId] += quantityTraded;
				simulation.moneyTraded[goodId] += money;
			}

			// Remove ask from list if seller has sold he wanted inventory
			if((*ask).quantity == 0){
				(*ask).fulfilled = true;
				std::advance(ask,1);
			}

			// Remove bid from list if buyer has gotten all he wanted
			if((*bid).quantity == 0){
				(*bid).fulfilled = true;
				std::advance(bid, 1);
			}
		}
	}
}

float MarketSystem::getPrice(Simulation &simulation, unsigned int agentId, unsigned int goodId, bool isSelling)
{
	if(simulation.agents[agentId].lastOfferFulfilled[goodId] == true){
		// If last offer was fulfilled, maintain same price
		return simulation.agents[agentId].offerPrice[goodId];
	}else{
		// If last offer was unfulfilled, adjust price depending on wether or not agent is selling or not
		if(isSelling){
			return simulation.agents[agentId].offerPrice[goodId] * (1 - PRICE_CHANGE_FACTOR);
		}else{
			return simulation.agents[agentId].offerPrice[goodId] * (1 + PRICE_CHANGE_FACTOR);
		}
	}
}