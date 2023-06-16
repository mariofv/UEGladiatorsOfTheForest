

using UnrealBuildTool;
using System.Collections.Generic;

public class UEGladiatorsOfTheForestEditorTarget : TargetRules
{
	public UEGladiatorsOfTheForestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UEGladiatorsOfTheForest" } );
	}
}
