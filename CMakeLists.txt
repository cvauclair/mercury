cmake_minimum_required(VERSION 3.10)

project(mercury)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Find threading library
find_package(Threads)

find_package(Lua REQUIRED)
set(LUA_LIBRARIES "/usr/lib/liblua5.3.so")

set(simulationSRCS
    src/configloader.cpp
	src/consumptionsystem.cpp
	src/marketsystem.cpp
	src/productionsystem.cpp
	src/simulation.cpp
	src/simulationmanager.cpp
	src/statsmanager.cpp
)
add_library(simulation SHARED ${simulationSRCS})

set(utilitySRCS
	src/utility/logger.cpp
)
add_library(utility SHARED ${utilitySRCS})

set(testSRCS
	test/test.cpp
)

set(mercurySRCS
	src/main.cpp
)

include_directories(src/utility src include src/vizualizer ${LUA_INCLUDE_DIR})

# Simulation
add_executable(mercury ${mercurySRCS})
target_link_libraries(mercury simulation utility ${LUA_LIBRARIES})

# Tests
add_executable(test ${testSRCS})
target_link_libraries(test simulation utility ${LUA_LIBRARIES})

