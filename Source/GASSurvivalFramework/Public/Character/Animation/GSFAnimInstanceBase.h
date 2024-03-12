// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GEAnimInstance.h"
#include "GSFAnimInstanceBase.generated.h"

class UCharacterMovementComponent;

/**
 * 속도, 방향 등 대부분의 캐릭터 애니메이션 블루프린트에서 필요한 값들을 멤버 변수로 지닌 클래스입니다.
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFAnimInstanceBase : public UGEAnimInstance
{
	GENERATED_BODY()

	TWeakObjectPtr<ACharacter> Character;

	TWeakObjectPtr<UCharacterMovementComponent> CharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "State|Movement", meta = (AllowPrivateAccess = true))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "State|Movement", meta = (AllowPrivateAccess = true))
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "State|Movement", meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "State|Movement", meta = (AllowPrivateAccess = true))
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly, Category = "State|Character", meta = (AllowPrivateAccess = true))
	bool bFalling;

	UPROPERTY(BlueprintReadOnly, Category = "State|Character", meta = (AllowPrivateAccess = true))
	bool bCrouching;

    UPROPERTY(BlueprintReadOnly, Category = "State|Character", meta = (AllowPrivateAccess = true))
    bool bADS;

    UPROPERTY(BlueprintReadOnly, Category = "State|Character", meta = (AllowPrivateAccess = true))
    bool bCombat;

    UPROPERTY(BlueprintReadOnly, Category = "State|Character", meta = (AllowPrivateAccess = true))
    bool bDead;

	UPROPERTY(BlueprintReadOnly, Category = "State|AimOffset", meta = (AllowPrivateAccess = true))
	float AimYaw;

	UPROPERTY(BlueprintReadOnly, Category = "State|AimOffset", meta = (AllowPrivateAccess = true))
	float AimPitch;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "State|AimOffset", meta = (AllowPrivateAccess = true))
	float InterpSpeed = 15.f;

public:
    UGSFAnimInstanceBase();

    /* AnimInstance */

    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
    /* GEAnimInstance */

    virtual void OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount) override;

    /* Getter */

	UFUNCTION(BlueprintPure)
	FORCEINLINE ACharacter* GetCharacter() const { return Character.Get(); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UCharacterMovementComponent* GetCharacterMovement() const { return CharacterMovement.Get(); }
};
