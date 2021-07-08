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
	
	static string getHummanityLevel(int hummanity)
	{
		HummanityValues hummanityValuesData = loadHummanityValues();
		
		array<ref HummanityLevel> hummanityLevels = hummanityValuesData.getHummanityLevels();
		int hummanityMax = 0;
		int hummanityMin = 0;
		string hummanityLevelName = "Survivor";

		for (int i = 0; i < hummanityLevels.Count(); i++)
		{
			hummanityMax = hummanityLevels[i].getMaxHummanity();
			hummanityMin = hummanityLevels[i].getMinHummanity();
			hummanityLevelName = hummanityLevels[i].getName();
			
			if (hummanity <= hummanityMax && hummanity > hummanityMin)
			{
				break;
			}
		 }
		
		return hummanityLevelName;
	}
	
	static string checkHummanityLevel(string playerID)
	{
		string playerJson = logsRoot + playerID + ".json";
		
		if (FileExist(playerJson))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			HummanityValues hummanityValuesData = new HummanityValues();
			
			JsonFileLoader<PlayerHummanityValues>.JsonLoadFile(playerJson, playerHummanityData);
			JsonFileLoader<HummanityValues>.JsonLoadFile(hummanityValuesPath, hummanityValuesData);
			
			
			return "Survivor";
		}
		else
		{
			return "Survivor";
		}
	}
	
	static void initPlayerLog(string playerID)
	{
		string playerJson = logsRoot + playerID + ".json";
		
		if (!FileExist(playerJson))
		{
			PlayerHummanityValues playerHummanityData = loadPlayerHummanityData(playerID);
			playerHummanityData.init();
		
			savePlayerHummanityData(playerHummanityData, playerID);
		}
	}
	
	static void handleKillZombie(string playerID) 
	{
		PlayerHummanityValues playerHummanityData = loadPlayerHummanityData(playerID);
		HummanityValues hummanityValuesData = loadHummanityValues();
		
		playerHummanityData.setHummanity(playerHummanityData.getHummanity() + hummanityValuesData.getHummanityForKillingZed());	
		playerHummanityData.setKilledZeds(playerHummanityData.getKilledZeds() + 1);
		
		string playerHummanityLevel = getHummanityLevel(playerHummanityData.getHummanity());
		
		playerHummanityData.setHummanityLevel(playerHummanityLevel);
		
		savePlayerHummanityData(playerHummanityData, playerID);
	}
	
	static void handlePlayerKill(string victimID, string killerID) 
	{
		if (victimID == killerID) 
		{
			return;
		}
		
		string victimLevel = checkHummanityLevel(victimID);
		
		PlayerHummanityValues killerHummanityData = loadPlayerHummanityData(killerID);
		PlayerHummanityValues victimHummanityData = loadPlayerHummanityData(victimID);
		
		//TODO reimplement handling player kill
	}
	
	static void handleDeath(string playerID) 
	{

		PlayerHummanityValues playerHummanityData = loadPlayerHummanityData(playerID);
		
		playerHummanityData.setDeaths(playerHummanityData.getDeaths() + 1);
		
		savePlayerHummanityData(playerHummanityData, playerID);
	}
}