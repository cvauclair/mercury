jobs = {
	wood_cutting = {
		id = 1,
		name = "Wood cutter",
		inputs = {
			{name = "TOOL", quantity = 1}
		}
		outputs = {
			{name = "WOOD", quantity = 4}
		}
	}	

	farming = {
		id = 2
		name = "Farmer",
		inputs = {
			{name = "TOOL", quantity = 1}
		}
		outputs = {
			{name = "FOOD", quantity = 10}
		}
	}	

	toolmaking = {
		id = 3,
		name = "Tool maker",
		inputs = {
			{name = "WOOD", quantity = 1},
			{name = "IRON", quantity = 2}
		}
		outputs = {
			{name = "TOOL", quantity = 1}
		}
	}	

	iron_mining = {
		id = 4,
		name = "Iron miner",
		inputs = {
			{name = "TOOL", quantity = 1}
		}
		outputs = {
			{name = "IRON", quantity = 5}
		}
	}	

	coal_mining = {
		id = 5,
		name = "Coal miner",
		inputs = {
			{name = "TOOL", quantity = 1}
		}
		outputs = {
			{name = "COAL", quantity = 4}
		}
	}	

	iron_smelting = {
		id = 6,
		name = "Coal miner",
		inputs = {
			{name = "IRON_ORE", quantity = 2},
			{name = "COAL", quantity = 1}
		}
		outputs = {
			{name = "IRON", quantity = 4}
		}
	}	
}
