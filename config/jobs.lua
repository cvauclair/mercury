jobs = {
	{
		id = 1,
		key = "WOOD_CUTTER",
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
		key = "FARMER",
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
		key = "TOOL_MAKER",
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
		key = "IRON_MINER",
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
		key = "COAL_MINER",
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
		key = "IRON_SMELTER",
		name = "Iron smelter",
		inputs = {
			{key = "IRON_ORE", quantity = 2},
			{key = "COAL", quantity = 1}
		},
		outputs = {
			{key = "IRON", quantity = 4}
		}
	}
}
