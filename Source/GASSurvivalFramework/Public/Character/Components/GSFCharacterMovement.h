// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GSFCharacterMovement.generated.h"

class UAbilitySystemComponent;

/**
 * 점프, 앉기 등 기본 캐릭터 움직임 상태에 따라 자동으로 게임플레이 태그를 부착 기능을 포함한 캐릭터 움직임 컴포넌트 클래스입니다.
 */
UCLASS(ClassGroup=(GASSurvivalFramework), meta=(BlueprintSpawnableComponent))
class GASSURVIVALFRAMEWORK_API UGSFCharacterMovement : public UCharacterMovementComponent
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

public:
    UGSFCharacterMovement();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* CharacterMovementComponent */

    virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;

    virtual bool CanAttemptJump() const override;
    virtual bool DoJump(bool bReplayingMoves) override;

    virtual void Crouch(bool bClientSimulation) override;
    virtual void UnCrouch(bool bClientSimulation) override;
};
