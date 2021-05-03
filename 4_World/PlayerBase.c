modded class PlayerBase
{
	override void OnConnect()
	{
		super.OnConnect();
		
		Man thisMan = this;
		
		//Init KillLogger
		FalconHeroesLogger.initPlayerLog(thisMan.GetIdentity().GetId());
	}
	
	 override void EEKilled( Object killer )
    {
		Man thisMan = this;
		
        FalconHeroesLogger.handleDeath(thisMan.GetIdentity().GetId());
		
		super.EEKilled(killer);
    }
}