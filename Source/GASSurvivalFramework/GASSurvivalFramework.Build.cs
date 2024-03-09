// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASSurvivalFramework : ModuleRules
{
	public GASSurvivalFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
            {

			}
			);


		PrivateIncludePaths.AddRange(
			new string[]
            {

			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                // 기본
				"Core",
                "EnhancedInput",

                // 이펙트
                "Niagara",

                // GAS
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",

                // 커스텀 플러그인
                "GASExtension"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                // 기본
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

                // 애니메이션
                "AnimGraphRuntime"
            }
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
	}
}
