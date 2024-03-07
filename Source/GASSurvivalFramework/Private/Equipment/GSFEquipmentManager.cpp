// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/GSFEquipmentManager.h"

#include "Equipment/GSFWeaponBase.h"

UGSFEquipmentManager::UGSFEquipmentManager()
{
    bWantsInitializeComponent = true;
}

void UGSFEquipmentManager::InitializeComponent()
{
    Super::InitializeComponent();

    // 의존성 주입
    SkeletalMesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();

    // 크기 할당
    EquippedEquipments.Reserve(EquipmentSocketNames.Num());
    EquippedWeapons.Reserve(EquippedWeapons.Num());
}

bool UGSFEquipmentManager::CanAddEquipment(TSubclassOf<AGSFEquipmentBase> EquipmentClass) const
{
    // null 검사
    if(EquipmentClass == nullptr) return false;

    // 비어있는 슬롯이 있는지 확인
    return EquipmentClass->IsChildOf(AGSFWeaponBase::StaticClass())
    ? WeaponSocketNames.Num() > EquippedWeapons.Num()
    : EquipmentSocketNames.Num() > EquippedEquipments.Num();
}

bool UGSFEquipmentManager::AddEquipment(TSubclassOf<AGSFEquipmentBase> EquipmentClass)
{
    // 추가 가능 여부 검사
    if(!CanAddEquipment(EquipmentClass)) return false;

    // Equipment 스폰
    AGSFEquipmentBase* SpawnedEquipment = SpawnEquipment(EquipmentClass);
    if(SpawnedEquipment == nullptr) return false;

    // Equipment 등록
    if(EquipmentClass->IsChildOf(AGSFWeaponBase::StaticClass()))
    {
        RegisterWeapon(Cast<AGSFWeaponBase>(SpawnedEquipment));
    }
    else
    {
        RegisterEquipment(SpawnedEquipment);
    }

    return true;
}

AGSFWeaponBase* UGSFEquipmentManager::GetWeapon(int32 Index)
{
    return *EquippedWeapons.Find(Index);
}

AGSFEquipmentBase* UGSFEquipmentManager::GetEquipment(int32 Index)
{
    return *EquippedEquipments.Find(Index);
}

void UGSFEquipmentManager::AttachEquipmentToSocket(AGSFEquipmentBase* Equipment, FName SocketName)
{
    // null 검사
    if(Equipment == nullptr) return;

    // 소켓 유효성 검사
    if(SkeletalMesh == nullptr || SocketName == NAME_None || SkeletalMesh->GetSocketByName(SocketName) == nullptr)
    {
        // 소켓에 부착하지 못하는 경우 Equipment를 숨깁니다.
        Equipment->SetHidden(true);
        return;
    }

    // 장비를 소켓에 부착
    Equipment->AttachToComponent(SkeletalMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
}

void UGSFEquipmentManager::RegisterEquipment(AGSFEquipmentBase* Equipment)
{
    // null 검사
    if(Equipment == nullptr) return;

    for(int32 i = 0; i < EquipmentSocketNames.Num(); i++)
    {
        // 이미 슬롯에 장비가 존재하는 경우 무시
        if(EquippedEquipments.Contains(i)) continue;

        // 슬롯에 장비 등록
        EquippedEquipments.Add(i, Equipment);
        AttachEquipmentToSocket(Equipment, EquipmentSocketNames[i]);
        break;
    }
}

void UGSFEquipmentManager::RegisterWeapon(AGSFWeaponBase* Weapon)
{
    // null 검사
    if(Weapon == nullptr) return;

    for(int32 i = 0; i < WeaponSocketNames.Num(); i++)
    {
        // 이미 슬롯에 무기가 존재하는 경우 무시
        if(EquippedWeapons.Contains(i)) continue;

        // 슬롯에 무기 등록
        EquippedWeapons.Add(i, Weapon);
        AttachEquipmentToSocket(Weapon, WeaponSocketNames[i]);
        break;
    }
}

AGSFEquipmentBase* UGSFEquipmentManager::SpawnEquipment(TSubclassOf<AGSFEquipmentBase> EquipmentClass) const
{
    // 월드 가져오기
    UWorld* World = GetWorld();

    // null 검사
    if(World == nullptr || EquipmentClass == nullptr) return nullptr;

    // Equipment 스폰
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.Owner = GetOwner();
    ActorSpawnParameters.Instigator = GetOwner()->GetInstigator();

    const FVector SpawnLocation = GetOwner()->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor(EquipmentClass, &SpawnLocation, &FRotator::ZeroRotator, ActorSpawnParameters);
    if(SpawnedActor == nullptr) return nullptr;

    return Cast<AGSFEquipmentBase>(SpawnedActor);
}
