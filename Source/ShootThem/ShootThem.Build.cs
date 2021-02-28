// Shoot Them Game, All Right Reserved

using UnrealBuildTool;

public class ShootThem : ModuleRules
{
	public ShootThem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[]{
		"ShootThem/Public/Player",
		"ShootThem/Public/Components",
		"ShootThem/Public/Dev",
		"ShootThem/Public/Weapon", 
		"ShootThem/Public/UI",
		"ShootThem/Public/Animations",
		"ShootThem/Public/Pickups",
		"ShootThem/Public/Weapon/Components",
		"ShootThem/Public/AI",
		"ShootThem/Public/AI/Tasks"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
