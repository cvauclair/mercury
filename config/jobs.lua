jobs = {
	{
		id = 1,
		name = "Wood cutter",
		inputs = {
			{key = "TOOL", quantity = 1}
		},
		outputs = {
			{key = "WOOD", quantity = 4}
		}
	},
	{
		id = 2,
		name = "Farmer",
		inputs = {
			{key = "TOOL", quantity = 1}
		},
		outputs = {
			{key = "FOOD", quantity = 10}
		}
	},
	{
		id = 3,
		name = "Tool maker",
		inputs = {
			{key = "WOOD", quantity = 1},
			{key = "IRON", quantity = 2}
		},
		outputs = {
			{key = "TOOL", quantity = 1}
		}
	},
	{
		id = 4,
		name = "Iron miner",
		inputs = {
			{key = "TOOL", quantity = 1}
		},
		outputs = {
			{key = "IRON", quantity = 5}
		}
	},
	{
		id = 5,
		name = "Coal miner",
		inputs = {
			{key = "TOOL", quantity = 1}
		},
		outputs = {
			{key = "COAL", quantity = 4}
		}
	},
	{
		id = 6,
		name = "Coal miner",
		inputs = {
			{key = "IRON_ORE", quantity = 2},
			{key = "COAL", quantity = 1}
		},
		outputs = {
			{key = "IRON", quantity = 4}
		}
	}
}
