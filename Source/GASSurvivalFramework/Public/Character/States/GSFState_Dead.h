// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GECharacterState.h"
#include "GSFState_Dead.generated.h"

/**
 *
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFState_Dead : public UGECharacterState
{
    GENERATED_BODY()

public:
    UGSFState_Dead();

    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
