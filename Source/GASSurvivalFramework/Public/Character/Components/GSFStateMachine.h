// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GEStateMachine.h"
#include "GSFStateMachine.generated.h"


UCLASS(ClassGroup=(GASSurvivalFramework), meta=(BlueprintSpawnableComponent))
class GASSURVIVALFRAMEWORK_API UGSFStateMachine : public UGEStateMachine
{
    GENERATED_BODY()

public:
    UGSFStateMachine();
};
