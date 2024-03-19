// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/GSFAnimInstanceBase.h"

#include "GEGameplayTags.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGSFAnimInstanceBase::UGSFAnimInstanceBase()
{
    TagsToRegister.AddTagFast(GEGameplayTags::State::FallingTag);
    TagsToRegister.AddTagFast(GEGameplayTags::State::CrouchingTag);
    TagsToRegister.AddTagFast(GEGameplayTags::State::ADSTag);
    TagsToRegister.AddTagFast(GEGameplayTags::State::DeadTag);
}

void UGSFAnimInstanceBase::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if(Character.IsValid())
		CharacterMovement = Character->GetCharacterMovement();
}

void UGSFAnimInstanceBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	// 유효성 검사
	if(!Character.IsValid() || !CharacterMovement.IsValid()) return;

    // 죽은 상태에서는 업데이트 중지
    if(bDead) return;

	/* CharacterMovement */

	// 속도
	Velocity = CharacterMovement->GetLastUpdateVelocity();
	GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Length();
	bShouldMove = !CharacterMovement->GetCurrentAcceleration().IsNearlyZero() && GroundSpeed > 3.f;
	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Character->GetActorRotation());

	// 에임 오프셋
	const FRotator TargetRotator = (Character->GetBaseAimRotation() - Character->GetActorRotation()).GetNormalized();
	const FRotator CurrentRotator = FRotator(AimPitch, AimYaw, 0.f);
	const FRotator DesiredRotator = FMath::RInterpTo(CurrentRotator, TargetRotator, DeltaSeconds, InterpSpeed);

	AimPitch = FMath::Clamp(DesiredRotator.Pitch, -90.f, 90.f);
	AimYaw = FMath::Clamp(DesiredRotator.Yaw, -90.f, 90.f);
	AimYaw += AimYaw - DesiredRotator.Yaw; // 초과한 각도만큼 다시 원복함으로써 -180 에서 180 으로 한 번에 넘어가는 것을 방지
}

void UGSFAnimInstanceBase::OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount)
{
    Super::OnGameplayEffectTagCountChanged_Event(Tag, NewCount);

    const bool bTriggered = NewCount > 0;

    if(Tag.MatchesTag(GEGameplayTags::State::FallingTag))
        bFalling = bTriggered;
    else if(Tag.MatchesTag(GEGameplayTags::State::CrouchingTag))
        bCrouching = bTriggered;
    else if(Tag.MatchesTag(GEGameplayTags::State::ADSTag))
        bADS = bTriggered;
    else if(Tag.MatchesTag(GEGameplayTags::State::DeadTag))
        bDead = bTriggered;
}
