class FalconHeroesLogger
{
	const static string logsRoot = "$profile:/FH/";
	const static string hummanityValues = "$profile:/FValues/FHvalues.json";
	
	static void initPlayerLog(string playerID)
	{
		string fileName = logsRoot + playerID + ".json";
		
		if (!FileExist(fileName))
		{
			map<string, int> jsonData = new map<string, int>();
			
			jsonData.Set("Hummanity", 2500);
			jsonData.Set("KilledPlayers", 0);
			jsonData.Set("KilledZeds", 0);
			jsonData.Set("Deaths", 0);
			
			JsonFileLoader<map<string, int>>.JsonSaveFile(fileName, jsonData);
		}
	}
	
	static void handleKillZombie(string playerID) 
	{
		string fileName = logsRoot + playerID + ".json";
		
		if (FileExist(fileName))
		{
			map<string, int> playerJsonData = new map<string, int>();
			map<string, int> valuesJsonData = new map<string, int>();
			
			JsonFileLoader<map<string, int>>.JsonLoadFile(fileName, playerJsonData);
			JsonFileLoader<map<string, int>>.JsonLoadFile(hummanityValues, valuesJsonData);
			
			int zombieKills = playerJsonData.Get("KilledZeds");
			int playerHummanity = playerJsonData.Get("Hummanity");
			int hummanityForZed = valuesJsonData.Get("HummanityForZed");
			
			playerHummanity += hummanityForZed;			
			
			playerJsonData.Set("KilledZeds", zombieKills + 1);
			playerJsonData.Set("Hummanity", playerHummanity);
			
			JsonFileLoader<map<string, int>>.JsonSaveFile(fileName, playerJsonData);
		}
	}
	
	static void handleDeath(string playerID) 
	{
		string fileName = logsRoot + playerID + ".json";
		
		if (FileExist(fileName))
		{
			map<string, int> playerJsonData = new map<string, int>();
			
			JsonFileLoader<map<string, int>>.JsonLoadFile(fileName, playerJsonData);
			
			int deaths = playerJsonData.Get("Deaths");		
			
			playerJsonData.Set("Deaths", deaths + 1);;
			
			JsonFileLoader<map<string, int>>.JsonSaveFile(fileName, playerJsonData);
		}
	}
}