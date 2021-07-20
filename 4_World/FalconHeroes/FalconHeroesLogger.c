class FalconHeroesLogger
{
	const static string logsRoot = "$profile:/FH/";
	const static string hummanityValuesPath = "$profile:/FValues/FHvalues.json";
	
	
	static PlayerHummanityValues loadPlayerHummanityData(string playerID)
	{
		string playerJsonPath = logsRoot + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			
			JsonFileLoader<PlayerHummanityValues>.JsonLoadFile(playerJsonPath, playerHummanityData);
			
			return playerHummanityData;
		}	
		
		return null;
	}
	
	static void savePlayerHummanityData(PlayerHummanityValues playerHummanityData, string playerID)
	{
		string playerJsonPath = logsRoot + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			JsonFileLoader<PlayerHummanityValues>.JsonSaveFile(playerJsonPath, playerHummanityData);
		}	
	}
	
	static HummanityValues loadHummanityValues()
	{
		if (FileExist(hummanityValuesPath))
		{
			HummanityValues hummanityValuesData = new HummanityValues();
			
			JsonFileLoader<HummanityValues>.JsonLoadFile(hummanityValuesPath, hummanityValuesData);
			
			return hummanityValuesData;
		}
		
		return null;
	}
	
	static bool checkIfInRange(int min, int value, int max)
	{
		if (((value - min) * (max - value)) >= 0)
        {
        	return true;
        }
        
        return false;
	}
	
	static string getHummanityLevel(int hummanity, string currentHummanityLevel)
	{
		HummanityValues hummanityValuesData = loadHummanityValues();
		
		array<ref HummanityLevel> hummanityLevels = hummanityValuesData.getHummanityLevels();
		int hummanityMax;
		int hummanityMin;
		string hummanityLevelName = currentHummanityLevel;

		for (int i = 0; i < hummanityLevels.Count(); i++)
		{
			hummanityMax = hummanityLevels[i].getMaxHummanity();
			hummanityMin = hummanityLevels[i].getMinHummanity();
			
			if (checkIfInRange(hummanityMin, hummanity, hummanityMax)) 
			{
				hummanityLevelName = hummanityLevels[i].getName();
				break;
			}
		 }
		
		return hummanityLevelName;
	}
	
	static void initPlayerLog(string playerID)
	{
		string playerJson = logsRoot + playerID + ".json";
	
		if (!FileExist(playerJson))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			playerHummanityData.init();
		
			JsonFileLoader<PlayerHummanityValues>.JsonSaveFile(playerJson, playerHummanityData);
		}
	}
	
	static void handleKillZombie(string playerID) 
	{
		PlayerHummanityValues playerHummanityData = loadPlayerHummanityData(playerID);
		HummanityValues hummanityValuesData = loadHummanityValues();
		
		playerHummanityData.setHummanity(playerHummanityData.getHummanity() + hummanityValuesData.getHummanityForKillingZed());	
		playerHummanityData.setKilledZeds(playerHummanityData.getKilledZeds() + 1);
		
		string playerHummanityLevel = getHummanityLevel(playerHummanityData.getHummanity(), playerHummanityData.getHummanityLevel());
		
		playerHummanityData.setHummanityLevel(playerHummanityLevel);
		
		savePlayerHummanityData(playerHummanityData, playerID);
	}
	
	static void handlePlayerKill(string victimID, string killerID) 
	{
		if (victimID == killerID) 
		{
			return;
		}
		
		HummanityValues hummanityValuesData = loadHummanityValues();
		
		PlayerHummanityValues killerHummanityData = loadPlayerHummanityData(killerID);
		PlayerHummanityValues victimHummanityData = loadPlayerHummanityData(victimID);
		
		int newHummanity = -(victimHummanityData.getHummanity() * hummanityValuesData.getHummanityMultiplier());
		
		killerHummanityData.setKilledPlayers(killerHummanityData.getKilledPlayers() + 1);
		killerHummanityData.setHummanity(killerHummanityData.getHummanity() + newHummanity);
		killerHummanityData.setHummanityLevel(getHummanityLevel(killerHummanityData.getHummanity(), killerHummanityData.getHummanityLevel()));
		
		savePlayerHummanityData(killerHummanityData, killerID);
	}
	
	static void handleDeath(string playerID) 
	{

		PlayerHummanityValues playerHummanityData = loadPlayerHummanityData(playerID);
		
		playerHummanityData.setDeaths(playerHummanityData.getDeaths() + 1);
		
		savePlayerHummanityData(playerHummanityData, playerID);
	}
}