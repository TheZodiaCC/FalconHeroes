class PlayerHummanityValues
{
	private int killedPlayers;
	private int killedZeds;
	private int hummanity;
	private int deaths;
	private string hummanityLevel;
	
	
	void init() {
		this.killedPlayers = 0;
		this.killedZeds = 0;
		this.hummanity = 0;
		this.deaths = 0;
		this.hummanityLevel = "Survivor";
	}
	
	int getKilledPlayers() {
		return killedPlayers;
	}
	
	int getKilledZeds() {
		return killedZeds;
	}
	
	int getHummanity() {
		return hummanity;
	}
	
	int getDeaths() {
		return deaths;
	}
	
	string getHummanityLevel() {
		return hummanityLevel;
	}
	
	void setHummanityLevel(string value) {
		this.hummanityLevel = value;
	}
	
	void setKilledPlayers(int value) {
		this.killedPlayers+= value;
	}
	
	void setKilledZeds(int value) {
		this.killedZeds = value;
	}
	
	void setHummanity(int value) {
		this.hummanity = value;
	}
	
	void setDeaths(int value) {
		this.deaths = value;
	}
}