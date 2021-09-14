class HumanityValues
{
	private int humanityForKillingZed;
	private float humanityMultiplier;
	private ref array<ref HumanityLevel> humanityLevels = new array<ref HumanityLevel>();
	
	int getHumanityForKillingZed() {
		return humanityForKillingZed;
	}
	
	float getHumanityMultiplier() {
		return humanityMultiplier;
	}
	
	array<ref HumanityLevel> getHumanityLevels() {
		return humanityLevels;
	}
}