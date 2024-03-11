// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GSFWeaponBase.h"

#include "GameFramework/Character.h"

void AGSFWeaponBase::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(NewOwner == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGSFWeaponBase::OnRep_Owner()
{
    Super::OnRep_Owner();

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGSFWeaponBase::PlayMontage(UAnimMontage* Montage)
{
    if(CharacterAnimInstance)
        CharacterAnimInstance->Montage_Play(Montage);
}

void AGSFWeaponBase::OnUnEquip_Implementation()
{
    CharacterAnimInstance = nullptr;
}

void AGSFWeaponBase::OnEquip_Implementation()
{
    const ACharacter* Character = Cast<ACharacter>(GetOwner());
    CharacterAnimInstance = Character == nullptr ? nullptr : Character->GetMesh()->GetAnimInstance();
}
