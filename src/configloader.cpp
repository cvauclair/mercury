#include "configloader.h"

ConfigLoader::ConfigLoader()
{

}

ConfigLoader::~ConfigLoader()
{

}

void ConfigLoader::loadConfig()
{

}

void ConfigLoader::loadGoodsConfig(const char *filename)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int lscript = luaL_dofile(L, filename);

	luabridge::LuaRef goodsRef = luabridge::getGlobal(L, "goods");
	for(unsigned int i = 0; i < goodsRef.length(); ++i){
		std::cout << goodsRef[i+1]["id"].cast<std::string>() << ". " << goodsRef[i+1]["name"].cast<std::string>() << std::endl;
	}
}
