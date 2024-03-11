// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GSFWeaponBase.h"

#include "GameFramework/Character.h"

void AGSFWeaponBase::PlayCharacterMontage(UAnimMontage* Montage)
{
    if(CharacterAnimInstance)
        CharacterAnimInstance->Montage_Play(Montage);
}

void AGSFWeaponBase::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    const ACharacter* Character = Cast<ACharacter>(GetOwner());
    CharacterAnimInstance = Character == nullptr ? nullptr : Character->GetMesh()->GetAnimInstance();
}

void AGSFWeaponBase::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    CharacterAnimInstance = nullptr;
}
