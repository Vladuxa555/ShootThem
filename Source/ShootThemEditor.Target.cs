// Shoot Them Game, All Right Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThemEditorTarget : TargetRules
{
	public ShootThemEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootThem" } );
	}
}
