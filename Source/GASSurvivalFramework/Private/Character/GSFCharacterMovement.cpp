// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GSFCharacterMovement.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GSFGameplayTags.h"


void UGSFCharacterMovement::InitializeComponent()
{
    Super::InitializeComponent();

    // AbilitySystemComponent 약한 참조
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

void UGSFCharacterMovement::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
    // 게임플레이 태그 부착 혹은 제거
    if(OwnerAbilitySystem.IsValid())
    {
        switch (NewMovementMode)
        {
        case MOVE_Falling:
            OwnerAbilitySystem->AddLooseGameplayTag(GSFGameplayTags::State::FallingTag);
            break;
        default:
            if(MovementMode == MOVE_Falling)
            {
                OwnerAbilitySystem->RemoveLooseGameplayTag(GSFGameplayTags::State::FallingTag);
            }
            break;
        }
    }

    Super::SetMovementMode(NewMovementMode, NewCustomMode);
}

void UGSFCharacterMovement::Crouch(bool bClientSimulation)
{
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->AddLooseGameplayTag(GSFGameplayTags::State::CrouchingTag);
    }

    Super::Crouch(bClientSimulation);
}

void UGSFCharacterMovement::UnCrouch(bool bClientSimulation)
{
    if(OwnerAbilitySystem.IsValid())
    {
        OwnerAbilitySystem->RemoveLooseGameplayTag(GSFGameplayTags::State::CrouchingTag);
    }

    Super::UnCrouch(bClientSimulation);
}
