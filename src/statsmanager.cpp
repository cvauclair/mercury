#include "statsmanager.h"

StatsManager::StatsManager()
{

}

StatsManager::~StatsManager()
{

}

void StatsManager::exportStats(const std::string &filename)
{
	// Open file
	std::ofstream file;
	file.open(filename);

	unsigned int goodId = 0;	// Init variable for reuse in loops

	// Write column labels

	// Write asks and bids labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "asks,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "bids,";
	}

	// Write fulfilled asks and bids labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "fulfilledasks,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "fulfilledbids,";
	}

	// Write qty consumed, produced and traded labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "qtyconsumed,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "qtyproduced,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "qtytraded,";
	}

	// Write money traded and average price labels
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "moneytraded,";
	}
	for(goodId = 0; goodId < MAX_GOODS; goodId++){
		file << "good" << goodId << "avgprice,";
	}

	// Newline
	file << std::endl;

	// Write actual data
	for(unsigned int day = 0; day < stats.size(); day++){
		// Write asks and bids
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].asksNb[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].bidsNb[goodId] << ",";
		}

		// Write fulfilled asks and bids
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].fulfilledAsksNb[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].fulfilledBidsNb[goodId] << ",";
		}

		// Write qty consumed, produced and traded
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].quantityConsumed[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].quantityProduced[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].quantityTraded[goodId] << ",";
		}

		// Write money traded and average price
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].moneyTraded[goodId] << ",";
		}
		for(goodId = 0; goodId < MAX_GOODS; goodId++){
			file << this->stats[day].averagePrice[goodId] << ",";
		}

		// Newline
		file << std::endl;
	}

	file.close();
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

