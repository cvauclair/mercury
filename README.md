# mercury, an economic simulator

## Description
Mercury is an economic simulator where agents consume and produce different types of goods and sell them on the open market. Each agent has a job which dictates how that agent can transform some goods into other goods and a base consumption which models that fact that humans need to consume a base amount of goods (e.g.: food) to be able to survive. Every "day" of the simulation, each agent decides whether or not to change job (depending on whether or not his needs are satisfied) and how much of each good to buy (based his projected needs) and sell (based on his inventory). The agent than makes bid and ask offers to the market to buy and sell goods respectively. These offers are matched with the offers of other agents through an auction mechanism where the best ask (i.e.: the lowest priced ask) is bought first. The bids are ordered randomly to simulate the fact that in real life, the buyer who is willing to pay the most for an item does not necessarily get the first pick for that item. 

## Building
### Linux/Unix
After cloning the repository, simply run the following commands to build the project:
```
mkdir build
cd build
cmake ..
make
```

### Windows
The project has not been tested on windows. However, given that it does not use any Linux specific libraries, the code should compile on windows with CMake.

## How to run mercury
To run mercury, simply execute the `mercury` program located in the `build/` directory. The program should not display anything. After the simulation is run, the file `stats.csv` should be in the same directory as the executable. The csv file contains statistics on the simulation which can be analyzed using any tools or framework (e.g.: Microsoft Excel, python's Matplotlib...).

## Configuration
### Goods
Goods can be added to or removed from the simulation by modifying the `config/goods.lua` file. Each good must have an `id`, `key` and `name`.

### Jobs
Jobs can be added, removed or modified by modifying the `config/jobs.lua` file. Each job must have an `id`, `key` and `name`, as well as a list of inputs and outputs (each constiting of a pair of the goods' `key` and the goods' `quantity`).

### Planned features
GUI to see live statistics of the simulation.