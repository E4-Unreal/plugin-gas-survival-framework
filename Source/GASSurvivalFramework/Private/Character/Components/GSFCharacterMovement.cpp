// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/GSFCharacterMovement.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GSFGameplayTags.h"
#include "GameFramework/Character.h"


UGSFCharacterMovement::UGSFCharacterMovement()
{
    NavAgentProps.bCanCrouch = true;
}

void UGSFCharacterMovement::InitializeComponent()
{
    Super::InitializeComponent();

    // AbilitySystemComponent 약한 참조
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

void UGSFCharacterMovement::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
    if(MovementMode != NewMovementMode && OwnerAbilitySystem.IsValid())
    {
        // Falling 게임플레이 태그 부착 혹은 제거
        if(NewMovementMode == MOVE_Falling)
            OwnerAbilitySystem->AddLooseGameplayTag(GSFGameplayTags::State::FallingTag);
        else if(MovementMode == MOVE_Falling)
            OwnerAbilitySystem->RemoveLooseGameplayTag(GSFGameplayTags::State::FallingTag);
    }

    Super::SetMovementMode(NewMovementMode, NewCustomMode);
}

bool UGSFCharacterMovement::CanAttemptJump() const
{
    return IsJumpAllowed() && (IsMovingOnGround() || IsFalling());
}

bool UGSFCharacterMovement::DoJump(bool bReplayingMoves)
{
    if ( CharacterOwner && CharacterOwner->CanJump() )
    {
        // 위 아래로 움직일 수 없는 경우 점프를 할 수 없습니다.
        if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
        {
            // 앉은 상태에서 점프를 하는 경우 먼저 UnCrouch를 호출합니다.
            if(IsCrouching()) bWantsToCrouch = false;

            // 중력 관련 처리
            if (HasCustomGravity())
            {
                FVector GravityRelativeVelocity = RotateWorldToGravity(Velocity);
                GravityRelativeVelocity.Z = FMath::Max<FVector::FReal>(GravityRelativeVelocity.Z, JumpZVelocity);
                Velocity = RotateGravityToWorld(GravityRelativeVelocity);
            }
            else
            {
                Velocity.Z = FMath::Max<FVector::FReal>(Velocity.Z, JumpZVelocity);
            }

            // Falling 모드로 변경
            SetMovementMode(MOVE_Falling);

            return true;
        }
    }

    return false;
}

void UGSFCharacterMovement::Crouch(bool bClientSimulation)
{
    // Crouch 게임플레이 태그 부착
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->AddLooseGameplayTag(GSFGameplayTags::State::CrouchingTag);
    }

    Super::Crouch(bClientSimulation);
}

void UGSFCharacterMovement::UnCrouch(bool bClientSimulation)
{
    // Crouch 게임플레이 태그 제거
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->RemoveLooseGameplayTag(GSFGameplayTags::State::CrouchingTag);
    }

    Super::UnCrouch(bClientSimulation);
}
