// Shoot Them Game, All Right Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThemTarget : TargetRules
{
	public ShootThemTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootThem" } );
	}
}
