#include "statsmanager.h"

StatsManager::StatsManager()
{

}

StatsManager::~StatsManager()
{

}

void StatsManager::exportStats(const std::__cxx11::string &filename)
{
	// TODO
}

void StatsManager::init(unsigned int days)
{
	// Initialize stats array
	this->stats.reserve(days);
	for(int i = 0; i < days; i++){
		this->stats.push_back(DayStats<MAX_GOODS>());
	}
}

DayStats<MAX_GOODS> *StatsManager::getDayStats(int day)
{
	if(day < 0){
		return &this->stats[0];
	}else{
		return &this->stats[day];
	}
}

unsigned int StatsManager::getSamplingInterval()
{
	return samplingInterval;
}

void StatsManager::setSamplingInterval(unsigned int interval)
{
	samplingInterval = interval;
}

void StatsManager::print(unsigned int day)
{
	DayStats<MAX_GOODS> *ds = &this->stats[day];
	printf("[Day %d]\n", day + 1);
	printf("Good\tAsks\tBids\tFulfilled Asks (%)\tFulfilled Bids (%)\tMoney Traded\tAverage Price\n");
	for(int goodId = 0; goodId < MAX_GOODS; goodId++){
		printf("%s", goods[goodId].data());	// Good name
		printf("\t%d", ds->asksNb[goodId]);	// Number of asks
		printf("\t%d", ds->bidsNb[goodId]);	// Number of bids
		printf("\t%d (%f)", ds->fulfilledAsksNb[goodId], (ds->asksNb[goodId] != 0 ? 100.0*ds->fulfilledAsksNb[goodId]/(float)ds->asksNb[goodId] : 0));	// Number of fulfilled asks
		printf("\t%d (%f)", ds->fulfilledBidsNb[goodId], (ds->bidsNb[goodId] != 0 ? 100.0*ds->fulfilledBidsNb[goodId]/(float)ds->bidsNb[goodId] : 0));	// Number of fulfilled bids
		printf("\t%f", ds->moneyTraded[goodId]);	// Value of goods traded
		printf("\t\t%f\n", ds->averagePrice[goodId]);	// Average price
	}
}

