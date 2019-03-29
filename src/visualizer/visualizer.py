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

job_names = [
	"wood_cutter",
	"farmer",
	"toolmaker",
	"iron_miner",
	"coal_miner",
	"iron_smelter"
]

job_stats = [
	"number",
	"average_satisfaction",
	"average_balance"
]

def load_goods_data(data_filename):
	# Read raw data
	raw_data = pd.read_csv(data_filename)

	# Load goods stats
	goods_data = {}
	for i, goods_name in enumerate(goods_names):
		goods_data[goods_name] = raw_data.filter(like="good{}".format(i), axis=1)
		goods_data[goods_name].columns = goods_stats
	
	return goods_data

def load_jobs_data(data_filename):
	# Read raw data
	raw_data = pd.read_csv(data_filename)

	# Load jobs stats
	jobs_data = {}
	for i, job_name in enumerate(job_names):
		jobs_data[job_name] = raw_data.filter(like="job{}".format(i), axis=1)
		jobs_data[job_name].columns = job_stats
	
	return jobs_data

def add_subplot(subplot_id, name, data_label, data):
	plt.subplot(subplot_id)
	plt.ylabel(name)
	for key in data.keys():
		plt.plot(data[key].index.values, data[key][data_label], label=key)
	plt.legend()

# Check for stat file
if len(sys.argv) == 2:
	data_filename = sys.argv[1]
else:
	print("Usage: {} <data csv file>".format(sys.argv[0]))
	sys.exit()

# Read data
goods_data = load_goods_data(data_filename)
jobs_data = load_jobs_data(data_filename)

# Plot goods data
plt.figure(1)

add_subplot(331, 'Supply', 'supply', goods_data)
add_subplot(332, 'Asks', 'asks', goods_data)
add_subplot(333, 'Bids', 'bids', goods_data)

add_subplot(334, 'Average price', 'average_price', goods_data)
add_subplot(335, 'Fulfilled asks', 'fulfilled_asks', goods_data)
add_subplot(336, 'Fulfilled bids', 'fulfilled_bids', goods_data)

add_subplot(337, 'Quantity produced', 'quantity_produced', goods_data)
add_subplot(338, 'Quantity consumed', 'quantity_consumed', goods_data)
add_subplot(339, 'Quantity traded', 'quantity_traded', goods_data)

figManager = plt.get_current_fig_manager()
figManager.window.showMaximized()

# Plot jobs data
plt.figure(2)

add_subplot(311, 'Job', 'number', jobs_data)
add_subplot(312, 'Average satisfaction', 'average_satisfaction', jobs_data)
add_subplot(313, 'Average balance', 'average_balance', jobs_data)

figManager = plt.get_current_fig_manager()
figManager.window.showMaximized()

# Show
plt.show()

