modded class ZombieBase extends DayZInfected 
{
	void EEKilled( Object killer )
	{
		Weapon_Base weapon = Weapon_Base.Cast(killer);
		
		SurvivorBase killer_survivor = SurvivorBase.Cast(weapon.GetHierarchyRootPlayer());
		Man man_killer = killer_survivor;

		FalconHeroesLogger.handleKillZombie(man_killer.GetIdentity().GetId());
		
		super.EEKilled(killer);
	}
}