modded class MissionServer
{
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		FalconHeroesLoadouts.spawnLoadout(player);
	}
}