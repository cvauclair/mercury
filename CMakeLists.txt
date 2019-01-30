cmake_minimum_required(VERSION 3.10)

project(mercury)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Lua REQUIRED)
set(LUA_LIBRARIES "/usr/lib/liblua5.3.so")

set(simulationSRCS
#	src/agentmanager.cpp
    src/configloader.cpp
	src/consumptionsystem.cpp
	src/marketsystem.cpp
	src/productionsystem.cpp
	src/simulation.cpp
	src/simulationmanager.cpp
	src/statsmanager.cpp
)

set(testSRCS
	test/test.cpp
#	test/agentmanagertests.cpp
#	test/consumptionsystemtests.cpp
#	test/productionsystemtests.cpp
)

set(simSRCS
	src/main.cpp
)

include_directories(src include src/vizualizer ${LUA_INCLUDE_DIR})

add_library(simulation SHARED ${simulationSRCS})

# Simulation
add_executable(sim ${simSRCS})
target_link_libraries(sim simulation ${LUA_LIBRARIES})

# Tests
add_executable(test ${testSRCS})
target_link_libraries(test simulation ${LUA_LIBRARIES})

