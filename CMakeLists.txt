cmake_minimum_required(VERSION 2.8)

project(simulation)

set(simulationSRCS
	src/simulation.cpp
	src/statsmanager.cpp
)

set(testSRCS
	test/test.cpp
)

set(simSRCS
	src/main.cpp
)

include_directories(src)

add_library(simulation SHARED ${simulationSRCS})
add_executable(test ${testSRCS})
add_executable(sim ${simSRCS})
target_link_libraries(test simulation)
target_link_libraries(sim simulation)

