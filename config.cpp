class CfgPatches
{
	class FalconHeroes
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts"};
	};
};

class CfgMods
{
	class FalconHeroes
	{
	    dir = FalconHeroes
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = FalconHeroes
	    credits = "";
	    author = "";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "World", "Mission" };

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {
										"FalconHeroes/Defines",
										"FalconHeroes/4_World"
									};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {
									"FalconHeroes/Defines",
									"FalconHeroes/5_Mission"
									};
			};
		};
	};
};
