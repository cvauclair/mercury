#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

struct GoodsStats{
	GoodsStats(){}
	~GoodsStats(){}
	unsigned int numAsks = 0;
	unsigned int numBids = 0;
	unsigned int numFulfilledAsks = 0;
	unsigned int numFulfilledBids = 0;
	unsigned int quantityProduced = 0;
	unsigned int quantityConsumed = 0;
	unsigned int quantityTraded = 0;
	unsigned int totalSupply = 0;
	float moneyTraded = 0.0f;
	float averagePrice = 0.0f;
};

struct JobStats{
	JobStats(){
		this->numAgents = 0;
		this->averageSatisfaction = 0.0f;
		this->averageBalance = 0.0f;
	}
	~JobStats(){}
	unsigned int numAgents = 0;
	float averageSatisfaction = 0.0f;
	float averageBalance = 0.0f;
};

struct DayStats{
	DayStats(){}
	DayStats(unsigned int day, std::vector<GoodsStats> gStats, std::vector<JobStats> jStats): day(day), goodsStats(gStats), jobsStats(jStats) {}
	~DayStats(){
		this->goodsStats.clear();
		this->jobsStats.clear();
	}
	unsigned int day = 0;
	std::vector<GoodsStats> goodsStats;
	std::vector<JobStats> jobsStats;
};

#endif
