class FalconHeroesLogger
{
	const static string logsRoot = HeroesConsts.HUMMANITY_LOGS_DATA_DIR_PATH;
	const static string humanityValuesPath = HeroesConsts.HUMMANITY_VALUES_DATA_PATH;
	
	
	static PlayerHumanityValues loadPlayerHumanityData(string playerID)
	{
		string playerJsonPath = logsRoot + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			PlayerHumanityValues playerHumanityData = new PlayerHumanityValues();
			
			JsonFileLoader<PlayerHumanityValues>.JsonLoadFile(playerJsonPath, playerHumanityData);
			
			return playerHumanityData;
		}	
		
		return null;
	}
	
	static int getPlayerHumanity(string playerId)
	{
		PlayerHumanityValues humanityValues = loadPlayerHumanityData(playerId);
		
		if (humanityValues)
		{
			return humanityValues.getHumanity(); 
		}	
		
		return 0;
	}
	
	static HumanityLevel getHumanityLevelByName(string levelName)
	{
		HumanityValues humanityValuesData = loadHumanityValues();
		array<ref HumanityLevel> humanityLevels = new array<ref HumanityLevel>();
		HumanityLevel level;
		
		humanityLevels = humanityValuesData.getHumanityLevels();
		
		for (int i = 0; i < humanityLevels.Count(); i++)
		{
			if (humanityLevels[i].getName() == levelName)
			{
				level = humanityLevels[i];
				
				break;
			}
		}
		
		return level;
	}
	
	static int getHumanityMultiplier(PlayerHumanityValues killerHumanityData, PlayerHumanityValues victimHumanityData)
	{
		HumanityLevel killerLevel = getHumanityLevelByName(killerHumanityData.getHumanityLevel());
		HumanityLevel victimLevel = getHumanityLevelByName(victimHumanityData.getHumanityLevel());
		
		int victimHumanity = victimHumanityData.getHumanity();
		int humanityMultiplier = 1;
		
		if (victimHumanity >= 0)
		{
			humanityMultiplier = killerLevel.getPositiveHumanityMultiplier();
		}
		else
		{
			humanityMultiplier = killerLevel.getNegativeHumanityMultiplier();
		}
		
		return humanityMultiplier;
	}
	
	static void savePlayerHumanityData(PlayerHumanityValues playerHumanityData, string playerID)
	{
		string playerJsonPath = logsRoot + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			JsonFileLoader<PlayerHumanityValues>.JsonSaveFile(playerJsonPath, playerHumanityData);
		}	
	}
	
	static HumanityValues loadHumanityValues()
	{
		if (FileExist(humanityValuesPath))
		{
			HumanityValues humanityValuesData = new HumanityValues();
			
			JsonFileLoader<HumanityValues>.JsonLoadFile(humanityValuesPath, humanityValuesData);
			
			return humanityValuesData;
		}
		
		return null;
	}
	
	static string getHumanityLevel(int humanity, string currentHumanityLevel)
	{
		HumanityValues humanityValuesData = loadHumanityValues();
		array<ref HumanityLevel> humanityLevels = new array<ref HumanityLevel>();
		
		humanityLevels = humanityValuesData.getHumanityLevels();
		int humanityMax;
		int humanityMin;
		string humanityLevelName = currentHumanityLevel;

		for (int i = 0; i < humanityLevels.Count(); i++)
		{
			humanityMax = humanityLevels[i].getMaxHumanity();
			humanityMin = humanityLevels[i].getMinHumanity();
			
			if (humanity.InRange(humanityMin, humanityMax))
			{
				humanityLevelName = humanityLevels[i].getName();
				break;
			}
		 }
		
		return humanityLevelName;
	}
	
	static void initPlayerLog(string playerID)
	{
		string playerJson = logsRoot + playerID + ".json";
	
		if (!FileExist(playerJson))
		{
			PlayerHumanityValues playerHumanityData = new PlayerHumanityValues();
			playerHumanityData.init();
		
			JsonFileLoader<PlayerHumanityValues>.JsonSaveFile(playerJson, playerHumanityData);
		}
	}
	
	static void handleKillZombie(string playerID) 
	{
		PlayerHumanityValues playerHumanityData = loadPlayerHumanityData(playerID);
		HumanityValues humanityValuesData = loadHumanityValues();
		
		int newHumanity = playerHumanityData.getHumanity() + humanityValuesData.getHumanityForKillingZed();
		
		playerHumanityData.setHumanity(newHumanity);	
		playerHumanityData.setKilledZeds(playerHumanityData.getKilledZeds() + 1);
		
		string playerHumanityLevel = getHumanityLevel(playerHumanityData.getHumanity(), playerHumanityData.getHumanityLevel());
		
		playerHumanityData.setHumanityLevel(playerHumanityLevel);
		
		savePlayerHumanityData(playerHumanityData, playerID);
	}
	
	static void handlePlayerKill(string victimID, string killerID) 
	{
		if (victimID == killerID) 
		{
			return;
		}
		
		HumanityValues humanityValuesData = loadHumanityValues();
		
		PlayerHumanityValues killerHumanityData = loadPlayerHumanityData(killerID);
		PlayerHumanityValues victimHumanityData = loadPlayerHumanityData(victimID);
		
		int humanityMultiplier = getHumanityMultiplier(killerHumanityData, victimHumanityData);
		
		int newHumanity = humanityMultiplier * (victimHumanityData.getHumanity() * humanityValuesData.getHumanityMultiplier());
		
		killerHumanityData.setKilledPlayers(killerHumanityData.getKilledPlayers() + 1);
		killerHumanityData.setHumanity(killerHumanityData.getHumanity() + newHumanity);
		killerHumanityData.setHumanityLevel(getHumanityLevel(killerHumanityData.getHumanity(), killerHumanityData.getHumanityLevel()));
		
		savePlayerHumanityData(killerHumanityData, killerID);
	}
	
	#ifdef FALCON_MISSIONS
	static void handleFAIKill(string killerID, int missionLVL, string missionType) 
	{
		HumanityValues humanityValuesData = loadHumanityValues();
		
		PlayerHumanityValues killerHumanityData = loadPlayerHumanityData(killerID);
		
		int newHumanity = 0;
		
		if (missionType == FalconMissionsConsts.MISSION_TYPE_HEROES)
		{
			newHumanity = humanityValuesData.getHumanityForKillingHeroesAI() * missionLVL;
		}
		
		else if (missionType == FalconMissionsConsts.MISSION_TYPE_BANDITS)
		{
			newHumanity = humanityValuesData.getHumanityForKillingBanditsAI() * missionLVL;
		}
		
		killerHumanityData.setHumanity(killerHumanityData.getHumanity() + newHumanity);
		killerHumanityData.setHumanityLevel(getHumanityLevel(killerHumanityData.getHumanity(), killerHumanityData.getHumanityLevel()));
		
		savePlayerHumanityData(killerHumanityData, killerID);
	}
	#endif
	
	static void handleDeath(string playerID) 
	{

		PlayerHumanityValues playerHumanityData = loadPlayerHumanityData(playerID);
		
		playerHumanityData.setDeaths(playerHumanityData.getDeaths() + 1);
		
		savePlayerHumanityData(playerHumanityData, playerID);
	}
	
	static PlayerBase getPlayerById(string playerId)
	{
	    array<Man> players = new array<Man>();
		PlayerBase player;
		
		GetGame().GetPlayers(players);
		
		for (int i = 0; i < players.Count(); i++)
		{
			player = PlayerBase.Cast(players[i]);
			
			if (playerId == player.GetIdentity().GetId())
			{
				return player;
			}
		}
		
		return null;
	}
}