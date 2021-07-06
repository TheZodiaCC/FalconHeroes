class FalconHeroesLogger
{
	const static string logsRoot = "$profile:/FH/";
	const static string hummanityValues = "$profile:/FValues/FHvalues.json";
	
	static string checkHummanityLevel(string playerID)
	{
		string playerJson = logsRoot + playerID + ".json";
		
		if (FileExist(playerJson))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			HummanityValues hummanityValuesData = new HummanityValues();
			
			JsonFileLoader<PlayerHummanityValues>.JsonLoadFile(playerJson, playerHummanityData);
			JsonFileLoader<HummanityValues>.JsonLoadFile(hummanityValues, hummanityValuesData);
			
			foreach (HummanityLevel level : hummanityValuesData.getHummanityLevels()) {
				Print(level.getName());
			}
			return "Survivor";
		}
		else
		{
			return "Survivor";
		}
	}
	
	static void initPlayerLog(string playerID)
	{
		string fileName = logsRoot + playerID + ".json";
		
		if (!FileExist(fileName))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			playerHummanityData.init();
			
			JsonFileLoader<PlayerHummanityValues>.JsonSaveFile(fileName, playerHummanityData);
		}
	}
	
	static void handleKillZombie(string playerID) 
	{
		string fileName = logsRoot + playerID + ".json";
		
		if (FileExist(fileName))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			HummanityValues hummanityValuesData = new HummanityValues();
			
			JsonFileLoader<PlayerHummanityValues>.JsonLoadFile(fileName, playerHummanityData);
			JsonFileLoader<HummanityValues>.JsonLoadFile(hummanityValues, hummanityValuesData);
			
			playerHummanityData.setHummanity(playerHummanityData.getHummanity() + hummanityValuesData.getHummanityForKillingZed());	
			playerHummanityData.setKilledZeds(playerHummanityData.getKilledZeds() + 1);		
			
			JsonFileLoader<PlayerHummanityValues>.JsonSaveFile(fileName, playerHummanityData);
		}
	}
	
	static void handlePlayerKill(string victimID, string killerID) 
	{
		string killerFileName = logsRoot + killerID + ".json";
		
		if (victimID == killerID) 
		{
			return;
		}
		
		if (FileExist(killerFileName))
		{
			string victimLevel = checkHummanityLevel(victimID);
			string level;
			
			map<string, int> killerJsonData = new map<string, int>();
			map<string, int> valuesJsonData = new map<string, int>();
			
			JsonFileLoader<map<string, int>>.JsonLoadFile(killerFileName, killerJsonData);
			JsonFileLoader<map<string, int>>.JsonLoadFile(hummanityValues, valuesJsonData);
			
			int killerHummanity = killerJsonData.Get("Hummanity");
			int killedPlayers = killerJsonData.Get("KilledPlayers");
			
			level = "HummanityForKilling" + victimLevel;
			int hummanityForKillingPlayer = valuesJsonData.Get(level);
			
			killerHummanity += hummanityForKillingPlayer;			
			
			killerJsonData.Set("KilledPlayers", killedPlayers + 1);
			killerJsonData.Set("Hummanity", killerHummanity);
			
			JsonFileLoader<map<string, int>>.JsonSaveFile(killerFileName, killerJsonData);
		}
	}
	
	static void handleDeath(string playerID) 
	{
		string fileName = logsRoot + playerID + ".json";
		
		if (FileExist(fileName))
		{
			PlayerHummanityValues playerHummanityData = new PlayerHummanityValues();
			
			JsonFileLoader<PlayerHummanityValues>.JsonLoadFile(fileName, playerHummanityData);	
			
			playerHummanityData.setDeaths(playerHummanityData.getDeaths() + 1);
			
			JsonFileLoader<PlayerHummanityValues>.JsonSaveFile(fileName, playerHummanityData);
		}
	}
}