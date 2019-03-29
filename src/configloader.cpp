#include "configloader.h"

ConfigLoader::ConfigLoader()
{

}

ConfigLoader::~ConfigLoader()
{

}

void ConfigLoader::loadConfig()
{
	std::vector<Goods> goodsData = ConfigLoader::loadGoodsConfig("/home/christophe/Documents/Programming/mercury/config/goods.lua");
	for(Goods goods : goodsData){
		std::cout << "Loaded goods " << goods.key << std::endl;
	}

	std::vector<Job> jobsData = ConfigLoader::loadJobsConfig("/home/christophe/Documents/Programming/mercury/config/jobs.lua");
	for(Job job : jobsData){
		std::cout << "Loaded job " << job.name << ": ";
		for(std::pair<std::string, unsigned int> &input : job.inputs){
			std::cout << input.second << ":" << input.first << " ";
		}
		std::cout << " -> ";
		for(std::pair<std::string, unsigned int> &output : job.outputs){
			std::cout << output.second << ":" << output.first << std::endl;
		}
	}
}

std::vector<Goods> ConfigLoader::loadGoodsConfig(const char *filename)
{
	// Init lua stuff
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	std::vector<Goods> goods;

	// Read data
	if(luaL_dofile(L, filename) != 0){
		throw std::runtime_error("Error opening goods.lua");
	}
	luabridge::LuaRef goodsRef = luabridge::getGlobal(L, "goods");
	for(unsigned int i = 0; i < goodsRef.length(); ++i){
		goods.emplace_back(goodsRef[i+1]["id"].cast<unsigned int>(),
				goodsRef[i+1]["key"].cast<std::string>(),
				goodsRef[i+1]["name"].cast<std::string>());
	}

	return goods;
}

std::vector<Job> ConfigLoader::loadJobsConfig(const char *filename)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	Job job;
	std::vector<Job> jobs;

	// Read data
	if(luaL_dofile(L, filename) != 0){
		throw std::runtime_error("Error opening jobs.lua");
	}
	luabridge::LuaRef jobsRef = luabridge::getGlobal(L, "jobs");
	for(unsigned int i = 0; i < jobsRef.length(); ++i){
		// Clear job object
		job.inputs.clear();
		job.outputs.clear();

		// Load data
		job.id = jobsRef[i+1]["id"].cast<unsigned int>();
		job.key = jobsRef[i+1]["key"].cast<std::string>();
		job.name = jobsRef[i+1]["name"].cast<std::string>();
		for(unsigned int j = 0; j < jobsRef[i+1]["inputs"].length(); ++j){
			job.inputs.push_back(std::pair<std::string, unsigned int>(jobsRef[i+1]["inputs"][j+1]["key"].cast<std::string>(),
					jobsRef[i+1]["inputs"][j+1]["quantity"].cast<unsigned int>()));
		}

		for(unsigned int j = 0; j < jobsRef[i+1]["outputs"].length(); ++j){
			job.outputs.push_back(std::pair<std::string, unsigned int>(jobsRef[i+1]["outputs"][j+1]["key"].cast<std::string>(),
					jobsRef[i+1]["outputs"][j+1]["quantity"].cast<unsigned int>()));
		}

		// Add job
		jobs.push_back(job);
	}

	return jobs;
}


















