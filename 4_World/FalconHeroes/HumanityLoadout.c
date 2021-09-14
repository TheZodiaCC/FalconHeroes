class HumanityLoadout
{
	private string name;
	private ref array<string> headItems = new ref array<string>();
	private ref array<string> bodyItems = new ref array<string>();
	private ref array<string> pantsItems = new ref array<string>();
	private ref array<string> bootsItems = new ref array<string>();
	private ref array<string> items = new ref array<string>();
	
	string getName() {
		return name;
	}
	
	ref array<string> getHeadItems() {
		return headItems;
	}
	
	ref array<string> getBodyItems() {
		return bodyItems;
	}
	
	ref array<string> getPantsItems() {
		return pantsItems;
	}
	
	ref array<string> getBootsItems() {
		return bootsItems;
	}
	
	ref array<string> getItems() {
		return items;
	}
}