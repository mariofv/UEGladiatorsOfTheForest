

using UnrealBuildTool;
using System.Collections.Generic;

public class UEGladiatorsOfTheForestTarget : TargetRules
{
	public UEGladiatorsOfTheForestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UEGladiatorsOfTheForest" } );
	}
}
