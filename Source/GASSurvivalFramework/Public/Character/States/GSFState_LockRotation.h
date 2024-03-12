// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GECharacterState.h"
#include "GSFState_LockRotation.generated.h"

/**
 * 캐릭터 회전을 컨트롤러가 제어하는 상태입니다.
 * 조준 혹은 전투 상태에서 사용됩니다.
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFState_LockRotation : public UGECharacterState
{
    GENERATED_BODY()

public:
    UGSFState_LockRotation();

protected:
    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;
};
