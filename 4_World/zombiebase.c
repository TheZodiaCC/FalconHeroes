modded class ZombieBase extends DayZInfected 
{
	override void EEKilled( Object killer )
	{
		Weapon_Base weapon = Weapon_Base.Cast(killer);
		
		SurvivorBase killerSurvivor = SurvivorBase.Cast(weapon.GetHierarchyRootPlayer());
		Man manKiller = killerSurvivor;

		FalconHeroesLogger.handleKillZombie(manKiller.GetIdentity().GetId());
		
		super.EEKilled(killer);
	}
}