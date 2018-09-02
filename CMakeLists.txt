cmake_minimum_required(VERSION 2.8)

project(mercury)

set(simulationSRCS
#	src/agentmanager.cpp
	src/consumptionsystem.cpp
	src/productionsystem.cpp
	src/simulation.cpp
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

include_directories(src include)

add_library(simulation SHARED ${simulationSRCS})

# Simulation
add_executable(sim ${simSRCS})
target_link_libraries(sim simulation)

# Tests
add_executable(test ${testSRCS})
target_link_libraries(test simulation)

