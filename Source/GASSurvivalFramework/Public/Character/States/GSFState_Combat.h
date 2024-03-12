// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GEState.h"
#include "GSFState_Combat.generated.h"

/**
 * 전투 모드에 돌입합니다.
 * Attack 태그가 부착되면 자동으로 Combat 태그를 부착합니다.
 * Combat 태그는 Attack 태그가 제거되고 Duration 후에 제거됩니다.
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFState_Combat : public UGEState
{
    GENERATED_BODY()

    // 전투 상태에서 벗어나기 위한 시간입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    float Duration = 2.f;

    FTimerHandle ExitTimer;

public:
    UGSFState_Combat();

protected:
    virtual void OnEnter_Implementation() override;
    virtual void OnExit_Implementation() override;

private:
    FTimerManager& GetTimerManager() const;
    void RemoveCombatTag() const;
};
