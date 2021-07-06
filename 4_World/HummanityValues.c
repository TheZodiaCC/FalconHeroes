class HummanityValues
{
	private int hummanityForKillingZed;
	private ref array<ref HummanityLevel> hummanityLevels = new array<ref HummanityLevel>();
	
	int getHummanityForKillingZed() {
		return hummanityForKillingZed;
	}
	
	array<ref HummanityLevel> getHummanityLevels() {
		return hummanityLevels;
	}
}