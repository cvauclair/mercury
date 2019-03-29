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

#include "definitions.h"

static const unsigned int MAX_NAME_LENGTH = 32;

class ConfigLoader{
	public:
		ConfigLoader();
		~ConfigLoader();

		void loadConfig();

		static std::vector<Goods> loadGoodsConfig(const char *filename);
		static std::vector<Job> loadJobsConfig(const char *filename);

	private:

};

#endif
