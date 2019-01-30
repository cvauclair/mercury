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

def add_subplot(subplot_id, name, data_label):
	plt.subplot(subplot_id)
	plt.ylabel(name)
	for goods_name in goods_names:
		plt.plot(goods_data[goods_name].index.values, goods_data[goods_name][data_label], label=goods_name)
	plt.legend()

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
add_subplot(331, 'Supply', 'supply')
add_subplot(332, 'Asks', 'asks')
add_subplot(333, 'Bids', 'bids')

add_subplot(334, 'Average price', 'average_price')
add_subplot(335, 'Fulfilled asks', 'fulfilled_asks')
add_subplot(336, 'Fulfilled bids', 'fulfilled_bids')

add_subplot(337, 'Quantity produced', 'quantity_produced')
add_subplot(338, 'Quantity consumed', 'quantity_consumed')
add_subplot(339, 'Quantity traded', 'quantity_traded')



# Show
figManager = plt.get_current_fig_manager()
figManager.window.showMaximized()
plt.show()

