#define FALCON_MISSIONS


modded class PlayerBase
{
	override void OnConnect()
	{
		super.OnConnect();

		//Init KillLogger
		FalconHeroesLogger.initPlayerLog(this.GetIdentity().GetId());
	}
	
	override void EEKilled(Object killer)
    {
		Weapon_Base weapon = Weapon_Base.Cast(killer);
		
		Man manKiller = Man.Cast(weapon.GetHierarchyRootPlayer());
		string killerID;
		
		if (this.IsInherited(FalconAI))
		{
			killerID = manKiller.GetIdentity().GetId();
			
			FalconAI fAI = FalconAI.Cast(this);
			
			FalconHeroesLogger.handleFAIKill(killerID, fAI.getMissionLVL(), fAI.getMissionType());
		}
		else
		{
			if (!CommitedSuicide()) 
			{
				string playerID = this.GetIdentity().GetId();
				
				killerID = manKiller.GetIdentity().GetId();
				
		        FalconHeroesLogger.handleDeath(playerID);
				FalconHeroesLogger.handlePlayerKill(playerID, killerID);
			}
		}
		
		super.EEKilled(killer);
    }
}