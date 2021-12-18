class PlayerHumanityValues
{
	private int killedPlayers;
	private int killedZeds;
	private int humanity;
	private int deaths;
	private string humanityLevel;
	
	
	void init() {
		this.killedPlayers = 0;
		this.killedZeds = 0;
		this.humanity = 2500;
		this.deaths = 0;
		this.humanityLevel = HeroesConsts.DEFAULT_HUMMANITY_LEVEL;
	}
	
	int getKilledPlayers() {
		return killedPlayers;
	}
	
	int getKilledZeds() {
		return killedZeds;
	}
	
	int getHumanity() {
		return humanity;
	}
	
	int getDeaths() {
		return deaths;
	}
	
	string getHumanityLevel() {
		return humanityLevel;
	}
	
	void setHumanityLevel(string value) {
		humanityLevel = value;
	}
	
	void setKilledPlayers(int value) {
		killedPlayers = value;
	}
	
	void setKilledZeds(int value) {
		killedZeds = value;
	}
	
	void setHumanity(int value) {
		humanity = value;
	}
	
	void setDeaths(int value) {
		deaths = value;
	}
}