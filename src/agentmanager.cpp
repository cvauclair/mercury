#include "agentmanager.h"

AgentManager::AgentManager()
{

}

AgentManager::~AgentManager()
{
	free(this->buffer);
}

void AgentManager::init(unsigned int popSize, unsigned int goodsNb)
{
	this->popSize = popSize;
	this->goodsNb = goodsNb;

	// Calculate buffer size
	unsigned int balancesBufferSize = popSize * sizeof(float);
	unsigned int jobIdsBufferSize = popSize * sizeof(bool);
	unsigned int stockpilesBufferSize = popSize * goodsNb * sizeof(char);
	unsigned int satisfactionsBufferSize = popSize * sizeof(float);
	unsigned int offerPricesBufferSize = popSize * goodsNb * sizeof(float);
	unsigned int lastOfferFulfilledBufferSize = popSize * goodsNb * sizeof(bool);
	this->bufferSize = balancesBufferSize + jobIdsBufferSize +
			stockpilesBufferSize + satisfactionsBufferSize + offerPricesBufferSize + lastOfferFulfilledBufferSize;

	// Allocate memory and zero it out
//	this->buffer = calloc(this->bufferSize, sizeof(char));
	this->buffer = malloc(this->bufferSize);

	// Set pointers
	this->balancesPtr = (float *)this->buffer;
	this->jobIdsPtr = (unsigned int *)(this->balancesPtr + balancesBufferSize);
	this->stockpilesPtr = (char *)(this->jobIdsPtr + jobIdsBufferSize);
	this->satifactionsPtr = (float *)(this->stockpilesPtr + stockpilesBufferSize);
	this->offerPricesPtr = (float *)(this->satifactionsPtr + satisfactionsBufferSize);
	this->lastOfferFulfilledPtr = (bool *)(this->offerPricesPtr + offerPricesBufferSize);
}

void AgentManager::setBalance(unsigned int agentId, float balance)
{
	*(this->balancesPtr + agentId * sizeof(float)) = balance;
}

void AgentManager::incrementBalance(unsigned int agentId, float increment)
{
	*(this->balancesPtr + agentId * sizeof(float)) += increment;
}

void AgentManager::decrementBalance(unsigned int agentId, float decrement)
{
	*(this->balancesPtr + agentId * sizeof(float)) -= decrement;
}

float &AgentManager::getBalance(unsigned int agentId)
{
	return *(this->balancesPtr + agentId * sizeof(float));
}

void AgentManager::setJobId(unsigned int agentId, unsigned int jobId)
{
	*(this->jobIdsPtr + agentId * sizeof(unsigned int)) = jobId;
}

unsigned int &AgentManager::getJobId(unsigned int agentId)
{
	return *(this->jobIdsPtr + agentId * sizeof(unsigned int));
}

void AgentManager::setGoodStockpileQuantity(unsigned int agentId, unsigned int goodId, char quantity)
{
	*(this->stockpilesPtr + agentId * this->goodsNb * sizeof(char) + goodId) = quantity;
}

void AgentManager::incrementGoodStockpileQuantity(unsigned int agentId, unsigned int goodId, char increment)
{
	*(this->stockpilesPtr + agentId * this->goodsNb * sizeof(char) + goodId) += increment;
}

void AgentManager::decrementGoodStockpileQuantity(unsigned int agentId, unsigned int goodId, char decrement)
{
	*(this->stockpilesPtr + agentId * this->goodsNb * sizeof(char) + goodId) -= decrement;
}

char &AgentManager::getGoodStockpileQuantity(unsigned int agentId, unsigned int goodId)
{
	return *(this->stockpilesPtr + agentId * this->goodsNb * sizeof(char) + goodId);
}

char *AgentManager::getStockpile(unsigned int agentId)
{
	return this->stockpilesPtr + agentId * this->goodsNb * sizeof(char);
}

void AgentManager::setSatisfaction(unsigned int agentId, float satisfaction)
{
	*(this->satifactionsPtr + agentId * sizeof(float)) = satisfaction;
}

float &AgentManager::getSatisfaction(unsigned int agentId)
{
	return *(this->satifactionsPtr + agentId * sizeof(float));
}

void AgentManager::setGoodOfferPrice(unsigned int agentId, unsigned int goodId, float price)
{
	*(this->offerPricesPtr + agentId * this->goodsNb * sizeof(float) + goodId) = price;
}

void AgentManager::incrementGoodOfferPrice(unsigned int agentId, unsigned int goodId, float increment)
{
	*(this->offerPricesPtr + agentId * this->goodsNb * sizeof(float) + goodId) += increment;
}

void AgentManager::decrementGoodOfferPrice(unsigned int agentId, unsigned int goodId, float decrement)
{
	*(this->offerPricesPtr + agentId * this->goodsNb * sizeof(float) + goodId) -= decrement;
}

float &AgentManager::getGoodOfferPrice(unsigned int agentId, unsigned int goodId)
{
	return *(this->offerPricesPtr + agentId * this->goodsNb * sizeof(float) + goodId);
}

float *AgentManager::getOfferPrices(unsigned int agentId)
{
	return this->offerPricesPtr + agentId * this->goodsNb * sizeof(float);
}

void AgentManager::setGoodLastOfferFulfilled(unsigned int agentId, unsigned int goodId, bool fulfilled)
{
	*(this->lastOfferFulfilledPtr + agentId * this->goodsNb * sizeof(char) + goodId) = fulfilled;
}

bool &AgentManager::getGoodLastOfferFulfilled(unsigned int agentId, unsigned int goodId)
{
	*(this->lastOfferFulfilledPtr + agentId * this->goodsNb * sizeof(char) + goodId);
}
