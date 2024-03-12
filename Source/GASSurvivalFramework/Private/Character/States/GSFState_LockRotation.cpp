// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GSFState_LockRotation.h"

#include "GSFGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGSFState_LockRotation::UGSFState_LockRotation()
{
    Triggers.AddTagFast(GSFGameplayTags::State::ADSTag);
    Triggers.AddTagFast(GSFGameplayTags::State::CombatTag);
}

void UGSFState_LockRotation::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    if(ACharacter* CachedCharacter = GetCharacter())
    {
        CachedCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
        CachedCharacter->bUseControllerRotationYaw = true;
    }
}

void UGSFState_LockRotation::OnExit_Implementation()
{
    Super::OnExit_Implementation();

    if(ACharacter* CachedCharacter = GetCharacter())
    {
        CachedCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
        CachedCharacter->bUseControllerRotationYaw = false;
    }
}
