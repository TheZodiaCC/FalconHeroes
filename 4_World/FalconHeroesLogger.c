class FalconHeroesLogger
{
	const static string logsRoot = "$profile:/FH/";
	const static string hummanityValues = "$profile:/FValues/FHvalues.json";
	
	static string checkHummanityLevel(string playerID)
	{
		map<string, int> playerData = new map<string, int>();
		map<string, int> hummanityLevels = new map<string, int>();
		
		string playerJson = logsRoot + playerID + ".json";
		
		if (FileExist(playerJson))
		{
			JsonFileLoader<map<string, int>>.JsonLoadFile(playerJson, playerData);
			JsonFileLoader<map<string, int>>.JsonLoadFile(hummanityValues, hummanityLevels);
			
			int hummanityForBandit = hummanityLevels.Get("HummanityForBandit");
			int hummanityForHero = hummanityLevels.Get("HummanityForHero");
			
			int playerHummanity = playerData.Get("Hummanity");
			
			if ((playerHummanity < hummanityForHero) && (playerHummanity > hummanityForBandit))
			{
				return "Survivor";
			}
			else if (playerHummanity >= hummanityForHero)
			{
				return "Hero";
			}
			else
			{
				return "Bandit";
			}
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
			map<string, int> playerJsonData = new map<string, int>();
			
			JsonFileLoader<map<string, int>>.JsonLoadFile(fileName, playerJsonData);
			
			int deaths = playerJsonData.Get("Deaths");		
			
			playerJsonData.Set("Deaths", deaths + 1);;
			
			JsonFileLoader<map<string, int>>.JsonSaveFile(fileName, playerJsonData);
		}
	}
}