// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GSFWeaponBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "FunctionLibraries/GEFunctionLibrary.h"

void AGSFWeaponBase::OnSelected_Implementation()
{
    GiveAbilities();
}

void AGSFWeaponBase::OnDeselected_Implementation()
{
    ClearAbilities();
}

void AGSFWeaponBase::GiveAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 부여
    AbilitySpecHandles = UGEFunctionLibrary::GiveAbilitiesToSystem(WeaponAbilities, OwnerAbilitySystem.Get());
}

void AGSFWeaponBase::ClearAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 제거
    for (const auto& AbilitySpecHandle : AbilitySpecHandles)
    {
        OwnerAbilitySystem->ClearAbility(AbilitySpecHandle);
    }
}

void AGSFWeaponBase::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    // AbilitySystem 캐싱
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

void AGSFWeaponBase::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    // AbilitySystem 캐시 제거
    OwnerAbilitySystem = nullptr;
}
