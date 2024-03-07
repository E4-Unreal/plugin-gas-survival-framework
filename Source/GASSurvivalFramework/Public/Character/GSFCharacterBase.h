// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GSFCharacterBase.generated.h"

/**
 * GSFCharacterMovement 컴포넌트로 교체된 캐릭터 클래스입니다.
 * 앉은 상태에서 점프가 가능하며, 앉기 해제 후 점프를 진행합니다.
 * 캐릭터 클래스에서는 CanJump만 수정되었으며 점프 시 앉기 해제 관련 코드는 GSFCharacterMovement::DoJump에 작성되어 있습니다.
 */

UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    AGSFCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    virtual bool CanJumpInternal_Implementation() const override;
    virtual bool CanCrouch() const override;
};
