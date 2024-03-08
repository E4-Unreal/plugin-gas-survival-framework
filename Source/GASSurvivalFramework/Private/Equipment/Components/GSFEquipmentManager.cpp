// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Components/GSFEquipmentManager.h"

#include "GameplayTagContainer.h"
#include "GSFBlueprintFunctionLibrary.h"
#include "Logging.h"
#include "Equipment/GSFWeaponBase.h"

const FEquipmentSlot FEquipmentSlot::EmptySlot;

void UGSFEquipmentManager::InitializeComponent()
{
    Super::InitializeComponent();

    CreateEquipmentSlots();
}

bool UGSFEquipmentManager::AddEquipment(TSubclassOf<AGSFEquipmentBase> WeaponClass)
{
    // 무기를 추가할 수 있는지 확인
    if(!CanAddEquipment(WeaponClass)) return false;

    // 무기 스폰
    AGSFWeaponBase* SpawnedWeapon = Cast<AGSFWeaponBase>(UGSFBlueprintFunctionLibrary::SpawnActorOnOwner(WeaponClass, GetOwner()));
    if(SpawnedWeapon == nullptr) return false;

    // 슬롯에 무기 추가
    const FGameplayTag& SlotTag = UGSFBlueprintFunctionLibrary::GetEquipmentSlot(WeaponClass);
    const FEquipmentSlot& EquipmentSlot = GetAvailableSlot(SlotTag);
    EquipmentSlots.Emplace(EquipmentSlot, SpawnedWeapon);

    // 무기를 스켈레탈 메시에 부착
    if(!UGSFBlueprintFunctionLibrary::AttachActorToSkeletalMeshSocket(SpawnedWeapon, GetMesh(), EquipmentSlot.SocketName))
    {
        // 부착에 실패한 경우 무기 비활성화
        SpawnedWeapon->SetActorHiddenInGame(true);
        LOG_CALLINFO(LogGASSurvivalFramework, Error)
    }

    return true;
}

void UGSFEquipmentManager::RemoveEquipment(FGameplayTag Slot, int32 Index)
{
    // 해당 슬롯에 장비 존재 유무 검사
    if(!IsEquipmentExist(Slot, Index)) return;

    // 장비 파괴
    const auto Equipment = GetEquipment(Slot, Index);
    Equipment->Destroy();

    // 슬롯 비우기
    ClearEquipmentSlot(Slot, Index);
}

void UGSFEquipmentManager::SelectEquipment(FGameplayTag Slot, int32 Index)
{
    // TODO 지금은 주 무기 슬롯만 가정
}

bool UGSFEquipmentManager::IsEquipmentExist(FGameplayTag Slot, int32 Index) const
{
    return GetEquipment(Slot, Index) != nullptr;
}

bool UGSFEquipmentManager::IsEquipmentSlotExist(FGameplayTag Slot, int32 Index) const
{
    return EquipmentSlots.Contains(FEquipmentSlot(Slot, Index));
}

AGSFEquipmentBase* UGSFEquipmentManager::GetEquipment(FGameplayTag Slot, int32 Index) const
{
    return IsEquipmentSlotExist(Slot, Index) ? *EquipmentSlots.Find(FEquipmentSlot(Slot, Index)) : nullptr;
}

void UGSFEquipmentManager::ClearEquipmentSlot(FGameplayTag Slot, int32 Index)
{
    // 장비 슬롯 유효성 검사
    if(!IsEquipmentSlotExist(Slot, Index)) return;

    // 장비 슬롯 비우기
    EquipmentSlots.Emplace(FEquipmentSlot(Slot, Index), nullptr);
}

bool UGSFEquipmentManager::CanAddEquipment(TSubclassOf<AGSFEquipmentBase> WeaponClass) const
{
    // 무기 슬롯이 비어있는지 확인
    const FGameplayTag& EquipmentSlot = UGSFBlueprintFunctionLibrary::GetEquipmentSlot(WeaponClass);
    return WeaponClass != nullptr && IsSlotAvailable(EquipmentSlot);
}

bool UGSFEquipmentManager::IsSlotAvailable(const FGameplayTag& WeaponSlot) const
{
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        // 장착 가능한 슬롯이 아닌 경우 무시
        if(EquipmentSlot != WeaponSlot) continue;

        // 이미 추가된 장비가 있는 경우 무시
        if(Equipment != nullptr) continue;

        // 빈 슬롯 발견
        return true;
    }

    return false;
}

const FEquipmentSlot& UGSFEquipmentManager::GetAvailableSlot(const FGameplayTag& WeaponSlot) const
{
    for (const auto& [EquipmentSlot, Equipment] : EquipmentSlots)
    {
        // 장착 가능한 슬롯이 아닌 경우 무시
        if(EquipmentSlot != WeaponSlot) continue;

        // 이미 추가된 장비가 있는 경우 무시
        if(Equipment != nullptr) continue;

        // 빈 슬롯 발견
        return EquipmentSlot;
    }

    return FEquipmentSlot::EmptySlot;
}

void UGSFEquipmentManager::CreateEquipmentSlots()
{
    for (const FEquipmentSlotConfig& EquipmentSlotConfig : EquipmentSlotConfigs)
    {
        const TArray<FName>& SocketNames = EquipmentSlotConfig.SocketNames;

        for(int i = 0; i < SocketNames.Num(); i++)
        {
            FEquipmentSlot EquipmentSlot
            {
                EquipmentSlotConfig.SlotTag,
                i,
                SocketNames[i]
            };

            EquipmentSlots.Add(EquipmentSlot);
        }
    }
}
