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
//		std::cout << "Loaded goods [" << goods.key << "]" << std::endl;
	}
}

std::vector<Goods> ConfigLoader::loadGoodsConfig(const char *filename)
{
	// Init lua stuff
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	std::vector<Goods> goods;

	// Read data
	int lscript = luaL_dofile(L, filename);
	luabridge::LuaRef goodsRef = luabridge::getGlobal(L, "goods");
	for(unsigned int i = 0; i < goodsRef.length(); ++i){
		goods.emplace_back(goodsRef[i+1]["id"].cast<unsigned int>(),
				goodsRef[i+1]["key"].cast<std::string>(),
				goodsRef[i+1]["name"].cast<std::string>());
	}

	return goods;
}

void ConfigLoader::loadJobsConfig(const char *filename)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int lscript = luaL_dofile(L, filename);

//	luabridge::LuaRef goodsRef = luabridge::getGlobal(L, "goods");
//	for(unsigned int i = 0; i < goodsRef.length(); ++i){
//		std::cout << goodsRef[i+1]["id"].cast<std::string>() << ". " << goodsRef[i+1]["name"].cast<std::string>() << std::endl;
//	}
}
