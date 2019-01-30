#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

class ConfigLoader{
	public:
		ConfigLoader();
		~ConfigLoader();

		void loadConfig();

		void loadGoodsConfig(const char *filename);

	private:

};

#endif
