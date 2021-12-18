class HumanityValues
{
	private int humanityForKillingZed;
	private int humanityForKillingHeroesAI;
	private int humanityForKillingBanditsAI;
	private float humanityMultiplier;
	private ref array<ref HumanityLevel> humanityLevels = new array<ref HumanityLevel>();
	
	int getHumanityForKillingZed() {
		return humanityForKillingZed;
	}
	
	float getHumanityMultiplier() {
		return humanityMultiplier;
	}
	
	float getHumanityForKillingHeroesAI() {
		return humanityForKillingHeroesAI;
	}
	
	float getHumanityForKillingBanditsAI() {
		return humanityForKillingBanditsAI;
	}
	
	array<ref HumanityLevel> getHumanityLevels() {
		return humanityLevels;
	}
}
