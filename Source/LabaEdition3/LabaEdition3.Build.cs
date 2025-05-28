// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LabaEdition3 : ModuleRules
{
	public LabaEdition3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
