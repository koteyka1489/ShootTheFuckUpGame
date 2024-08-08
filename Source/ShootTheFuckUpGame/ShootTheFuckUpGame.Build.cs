// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootTheFuckUpGame : ModuleRules
{
    public ShootTheFuckUpGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[]
        {
            "ShootTheFuckUpGame/Public/Components",
            "ShootTheFuckUpGame/Public/Dev",
            "ShootTheFuckUpGame/Public/Player",
            "ShootTheFuckUpGame/Public/UI",
            "ShootTheFuckUpGame/Public/Weapon",
            "ShootTheFuckUpGame/Public/Animations"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
