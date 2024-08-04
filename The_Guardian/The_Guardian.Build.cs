// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class The_Guardian : ModuleRules
{
	public The_Guardian(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","Niagara", "UMG", "NavigationSystem", "AIModule", "GameplayTasks" });
	}
}
