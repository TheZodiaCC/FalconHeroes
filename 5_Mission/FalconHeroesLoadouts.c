class FalconHeroesLoadouts
{
	const static string hummanityValues = "$profile:/FValues/FHvalues.json";
	const static string playersHummanityPath = "$profile:/FH/";
	
	static void spawnLoadout(PlayerBase player)
	{
		string playerID = player.GetIdentity().GetId();
		
		map<string, int> playerData = new map<string, int>();
		map<string, int> hummanityLevels = new map<string, int>();
		
		string playerJson = playersHummanityPath + playerID + ".json";
		
		if (FileExist(playerJson))
		{
			JsonFileLoader<map<string, int>>.JsonLoadFile(playerJson, playerData);
			JsonFileLoader<map<string, int>>.JsonLoadFile(hummanityValues, hummanityLevels);
			
			int hummanityForBandit = hummanityLevels.Get("HummanityForBandit");
			int hummanityForHero = hummanityLevels.Get("HummanityForHero");
			int playerHummanity = playerData.Get("Hummanity");
			
			player.RemoveAllItems();
			
			if ((playerHummanity < hummanityForHero) && (playerHummanity > hummanityForBandit))
			{
				spawnSurvivorLoadout(player);
			}
			else if (playerHummanity >= hummanityForHero)
			{
				spawnHeroLoadout(player);
			}
			else
			{
				spawnBanditLoadout(player);
			}
		}
		else
		{
			return;
		}
	}
	
	static void spawnSurvivorLoadout(PlayerBase player)
	{
		EntityAI itemClothing = player.FindAttachmentBySlotName("Body");
		EntityAI itemEnt;
		ItemBase itemBs;
		
		string body;
		string pants;
		string boots;
		int rndIndex;

		string tshirtArray[] = {"TShirt_Black", "TShirt_Blue", "TShirt_Green", "TShirt_Red"};
		rndIndex = Math.RandomInt(0, 4);
		
		body = tshirtArray[rndIndex];
		
		string pantsArray[] = {"Jeans_Black", "Jeans_Blue", "Jeans_Green", "Jeans_Brown"};
		rndIndex = Math.RandomInt(0, 4);
		
		pants = pantsArray[rndIndex];
		
		string bootsArray[] = {"AthleticShoes_Black", "AthleticShoes_Blue", "AthleticShoes_Green", "AthleticShoes_Brown"};
		rndIndex = Math.RandomInt(0, 4);
		
		boots = bootsArray[rndIndex];
		
		player.GetInventory().CreateInInventory(body);
		player.GetInventory().CreateInInventory(pants);
		player.GetInventory().CreateInInventory(boots);
		
		player.GetInventory().CreateInInventory("Plum");
		player.GetInventory().CreateInInventory("Roadflare");
		
		itemEnt = itemClothing.GetInventory().CreateInInventory("Rag");
		
		if (Class.CastTo(itemBs, itemEnt))
		{
			itemBs.SetQuantity(3);
		}
	}
	
	static void spawnHeroLoadout(PlayerBase player)
	{
		EntityAI itemClothing = player.FindAttachmentBySlotName("Body");
		EntityAI itemEnt;
		ItemBase itemBs;
		
		string body;
		string pants;
		string boots;
		int rndIndex;

		string tshirtArray[] = {"TacticalShirt_Black", "TacticalShirt_Grey", "TacticalShirt_Olive", "TacticalShirt_Tan"};
		rndIndex = Math.RandomInt(0, 4);
		
		body = tshirtArray[rndIndex];
		
		string pantsArray[] = {"CargoPants_Black", "CargoPants_Blue", "CargoPants_Green", "CargoPants_Grey"};
		rndIndex = Math.RandomInt(0, 4);
		
		pants = pantsArray[rndIndex];
		
		string bootsArray[] = {"CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		rndIndex = Math.RandomInt(0, 4);
		
		boots = bootsArray[rndIndex];
		
		player.GetInventory().CreateInInventory(body);
		player.GetInventory().CreateInInventory(pants);
		player.GetInventory().CreateInInventory(boots);
		
		player.GetInventory().CreateInInventory("BakedBeansCan");
		player.GetInventory().CreateInInventory("WaterBottle");
		player.GetInventory().CreateInInventory("PersonalRadio");
		player.GetInventory().CreateInInventory("Battery9V");
		player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("PoliceVest");
		player.GetInventory().CreateInInventory("Compass");
		player.GetInventory().CreateInInventory("HuntingKnife");
		player.GetInventory().CreateInInventory("CourierBag");
		player.GetInventory().CreateInInventory("Roadflare");
		player.GetInventory().CreateInInventory("Roadflare");
		
		itemEnt = itemClothing.GetInventory().CreateInInventory("Rag");
		
		if (Class.CastTo(itemBs, itemEnt))
		{
			itemBs.SetQuantity(6);
		}
	}
	
	static void spawnBanditLoadout(PlayerBase player)
	{
		EntityAI itemClothing = player.FindAttachmentBySlotName("Body");
		EntityAI itemEnt;
		ItemBase itemBs;
		
		string body;
		string pants;
		string boots;
		int rndIndex;

		string tshirtArray[] = {"BomberJacket_Black", "BomberJacket_Blue", "BomberJacket_Olive", "BomberJacket_Maroon"};
		rndIndex = Math.RandomInt(0, 4);
		
		body = tshirtArray[rndIndex];
		
		string pantsArray[] = {"Jeans_Black", "Jeans_Blue", "Jeans_Green", "Jeans_Brown"};
		rndIndex = Math.RandomInt(0, 4);
		
		pants = pantsArray[rndIndex];
		
		string bootsArray[] = {"WorkingBoots_Brown", "WorkingBoots_Grey", "WorkingBoots_Beige", "WorkingBoots_Green"};
		rndIndex = Math.RandomInt(0, 4);
		
		boots = bootsArray[rndIndex];
		
		player.GetInventory().CreateInInventory(body);
		player.GetInventory().CreateInInventory(pants);
		player.GetInventory().CreateInInventory(boots);
		
		player.GetInventory().CreateInInventory("Plum");
		player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("TunaCan");
		player.GetInventory().CreateInInventory("KitchenKnife");
		player.GetInventory().CreateInInventory("Roadflare");
		player.GetInventory().CreateInInventory("Roadflare");
		
		itemEnt = itemClothing.GetInventory().CreateInInventory("Rag");
		
		if (Class.CastTo(itemBs, itemEnt))
		{
			itemBs.SetQuantity(6);
		}
	}
}
