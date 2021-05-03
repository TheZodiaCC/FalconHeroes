modded class PlayerBase
{
	override void OnConnect()
	{
		super.OnConnect();

		//Init KillLogger
		FalconHeroesLogger.initPlayerLog(this.GetIdentity().GetId());
	}
	
	 override void EEKilled( Object killer )
    {
		string playerID = this.GetIdentity().GetId();
		
		Weapon_Base weapon = Weapon_Base.Cast(killer);
		
		SurvivorBase killerSurvivor = SurvivorBase.Cast(weapon.GetHierarchyRootPlayer());
		Man manKiller = killerSurvivor;
		
		string killerID = manKiller.GetIdentity().GetId();
		
        FalconHeroesLogger.handleDeath(playerID);
		FalconHeroesLogger.handlePlayerKill(playerID, killerID);
		
		super.EEKilled(killer);
    }
}