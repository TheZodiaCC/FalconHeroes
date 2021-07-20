class FalconHeroesLoadouts
{
	static ref array<ref HummanityLoadout> loadLoadoutsData() {
		const string loadoutsPath = "$profile:/FValues/FHloadouts.json";
		
		ref array<ref HummanityLoadout> hummanityLoadouts = new ref array<ref HummanityLoadout>();
		
		JsonFileLoader<ref array<ref HummanityLoadout>>.JsonLoadFile(loadoutsPath, hummanityLoadouts);
		
		return hummanityLoadouts;
	}
	
	static HummanityLoadout getLoadout(string playerHummanityLevel, ref array<ref HummanityLoadout> hummanityLoadouts) {
		for (int i = 0; i < hummanityLoadouts.Count(); i++) {
			if (hummanityLoadouts[i].getName() == playerHummanityLevel) {
				return hummanityLoadouts[i];
			}
		}
		
		return null;
	}
	
	static void spawnLoadout(PlayerBase player)
	{
		string playerID = player.GetIdentity().GetId();
		string playerHummanityLevel;
		array<ref HummanityLoadout> hummanityLoadouts;
		HummanityLoadout playerLoadout;
		array<string> bodyItems;
		array<string> pantsItems;
		array<string> bootsItems;
		array<string> items;
		
		string bodyItem;
		string pantsItem;
		string bootsItem;
		
		PlayerHummanityValues playerHummanityData = FalconHeroesLogger.loadPlayerHummanityData(playerID);
		playerHummanityLevel = playerHummanityData.getHummanityLevel();
		
		hummanityLoadouts = loadLoadoutsData();
		
		playerLoadout = getLoadout(playerHummanityLevel, hummanityLoadouts);
		
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
			
			foreach (string item : items) {
				player.GetInventory().CreateInInventory(item);
			}
		}
	}
}	
