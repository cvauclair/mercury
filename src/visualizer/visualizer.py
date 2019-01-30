#!/bin/python3

import matplotlib.pyplot as plt
import sys
import pandas as pd

# Config (will be moved to seperate config file later)
goods_names = [
	"wood", 
	"food", 
	"tool", 
	"iron_ore", 
	"coal", 
	"iron"
]

goods_stats = [
	"supply", 
	"asks", 
	"bids", 
	"fulfilled_asks", 
	"fulfilled_bids", 
	"quantity_consumed", 
	"quantity_produced", 
	"quantity_traded", 
	"money_traded",
	"average_price"
]

def load_goods_data(goods_data_filename):
	# Read raw data
	raw_data = pd.read_csv(goods_data_filename)

	# Load goods stats
	goods_data = {}
	for i, goods_name in enumerate(goods_names):
		goods_data[goods_name] = raw_data.filter(like="good{}".format(i), axis=1)
		goods_data[goods_name].columns = goods_stats
	
	return goods_data

# Check for stat file
if len(sys.argv) == 2:
	goods_data_filename = sys.argv[1]
else:
	print("Usage: {} <goods data csv file>".format(sys.argv[0]))
	sys.exit()

# Read goods data
goods_data = load_goods_data(goods_data_filename)

plt.figure(1)
# Plot goods supply
plt.subplot(231)
plt.ylabel('Supply')
for goods_name in goods_names:
	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].supply, label=goods_name)
plt.legend()

# Plot goods average price
plt.subplot(232)
plt.ylabel('Average price')
for goods_name in goods_names:
	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].average_price, label=goods_name)
plt.legend()

# Plot goods asks
plt.subplot(233)
plt.ylabel('Asks')
for goods_name in goods_names:
	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].asks, label=goods_name)
plt.legend()

# Plot goods bids
#plt.subplot(234)
#plt.ylabel('Bids')
#for goods_name in goods_names:
#	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].bids, label=goods_name)
#plt.legend()

# Plot goods quantity produced
plt.subplot(2,3,4)
plt.ylabel('Quantity produced')
for goods_name in goods_names:
	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].quantity_produced, label=goods_name)
plt.legend()

# Plot goods quantity consumed
plt.subplot(2,3,5)
plt.ylabel('Quantity consumed')
for goods_name in goods_names:
	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].quantity_consumed, label=goods_name)
plt.legend()

# Plot goods quantity traded
plt.subplot(2,3,6)
plt.ylabel('Quantity traded')
for goods_name in goods_names:
	plt.plot(goods_data[goods_name].index.values, goods_data[goods_name].quantity_traded, label=goods_name)
plt.legend()

# Show
figManager = plt.get_current_fig_manager()
figManager.window.showMaximized()
plt.show()

