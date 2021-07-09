class HummanityValues
{
	private int hummanityForKillingZed;
	private float hummanityMultiplier;
	private ref array<ref HummanityLevel> hummanityLevels = new array<ref HummanityLevel>();
	
	int getHummanityForKillingZed() {
		return hummanityForKillingZed;
	}
	
	float getHummanityMultiplier() {
		return hummanityMultiplier;
	}
	
	array<ref HummanityLevel> getHummanityLevels() {
		return hummanityLevels;
	}
}