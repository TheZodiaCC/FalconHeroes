class FalconHeroesLoadouts
{
	static ref array<ref HumanityLoadout> loadLoadoutsData() {
		const string loadoutsPath = HeroesConsts.HUMMANITY_LOADOUTS_DATA_PATH;
		
		ref array<ref HumanityLoadout> humanityLoadouts = new ref array<ref HumanityLoadout>();
		
		JsonFileLoader<ref array<ref HumanityLoadout>>.JsonLoadFile(loadoutsPath, humanityLoadouts);
		
		return humanityLoadouts;
	}
	
	static HumanityLoadout getLoadout(string playerHumanityLevel, ref array<ref HumanityLoadout> humanityLoadouts) {
		for (int i = 0; i < humanityLoadouts.Count(); i++) {
			if (humanityLoadouts[i].getName() == playerHumanityLevel) {
				return humanityLoadouts[i];
			}
		}
		
		return null;
	}
	
	static void spawnLoadout(PlayerBase player)
	{
		string playerID = player.GetIdentity().GetId();
		string playerHumanityLevel;
		array<ref HumanityLoadout> humanityLoadouts;
		HumanityLoadout playerLoadout;
		array<string> bodyItems;
		array<string> pantsItems;
		array<string> bootsItems;
		array<string> items;
		
		string bodyItem;
		string pantsItem;
		string bootsItem;
		
		string item;
		
		PlayerHumanityValues playerHumanityData = FalconHeroesLogger.loadPlayerHumanityData(playerID);
		playerHumanityLevel = playerHumanityData.getHumanityLevel();
		
		humanityLoadouts = loadLoadoutsData();
		
		playerLoadout = getLoadout(playerHumanityLevel, humanityLoadouts);
		
		if (playerLoadout != null) {
			player.RemoveAllItems();
		
			bodyItems = playerLoadout.getBodyItems();
			bodyItem = bodyItems[Math.RandomInt(0, bodyItems.Count())];
			
			pantsItems = playerLoadout.getPantsItems();
			pantsItem = pantsItems[Math.RandomInt(0, pantsItems.Count())];
			
			bootsItems = playerLoadout.getBootsItems();
			bootsItem = bootsItems[Math.RandomInt(0, bootsItems.Count())];
			
			items = playerLoadout.getItems();
			
			player.GetInventory().CreateInInventory(bodyItem);
			player.GetInventory().CreateInInventory(pantsItem);
			player.GetInventory().CreateInInventory(bootsItem);
			
			for (int i = 0; i < items.Count(); i++)
			{
				item = items[i];
				
				player.GetInventory().CreateInInventory(item);
			}
		}
	}
}	
