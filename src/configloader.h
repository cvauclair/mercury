#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <iostream>
#include <string>
#include <vector>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

static const unsigned int MAX_NAME_LENGTH = 32;

struct Goods{
	Goods(unsigned int id, std::string key, std::string name): id(id), key(key), name(name) {}
	unsigned int id = 0;
	std::string key = "";
	std::string name = "";
};

struct Job{
	Job(unsigned int id, std::string name): id(id), name(name) {}
	unsigned int id = 0;
	std::string name = "";
	std::vector<std::pair<unsigned int, unsigned int>> inputs;
	std::vector<std::pair<unsigned int, unsigned int>> outputs;
};

class ConfigLoader{
	public:
		ConfigLoader();
		~ConfigLoader();

		void loadConfig();

		static std::vector<Goods> loadGoodsConfig(const char *filename);
		static void loadJobsConfig(const char *filename);

	private:

};

#endif
