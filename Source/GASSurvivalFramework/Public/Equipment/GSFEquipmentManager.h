// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSFEquipmentBase.h"
#include "Components/ActorComponent.h"
#include "GSFEquipmentManager.generated.h"

class AGSFWeaponBase;

// TODO 현재는 무기 혹은 장비 슬롯이 증가만 하는 경우를 고려하고 있습니다. 감소하는 경우 인벤토리로 집어넣거나 떨구는 기능은 추후에 추가할 예정입니다.
// TODO 주 무기 슬롯, 보조 무기 슬롯이 존재할 수 있습니다. 나중에 구현 예정입니다.
/**
 * 장착된 장비를 관리하는 액터 컴포넌트입니다.
 * 장착된 장비를 적절한 스켈레탈 메시 소켓에 부착합니다.
 */
UCLASS(ClassGroup=(GASSurvivalFramework), meta=(BlueprintSpawnableComponent))
class GASSURVIVALFRAMEWORK_API UGSFEquipmentManager : public UActorComponent
{
    GENERATED_BODY()

    // 장비 혹은 무기를 부착할 스켈레탈 메시
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dependency", meta = (AllowPrivateAccess = true), Transient)
    USkeletalMeshComponent* SkeletalMesh;

    /* 무기 */

    // 장착 가능한 무기의 총 개수입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<FName> WeaponSocketNames;

    // 현재 장착된 무기입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    TMap<int32, AGSFWeaponBase*> EquippedWeapons;

    /* 장비 */

    // 장착 가능한 장비의 총 개수입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<FName> EquipmentSocketNames;

    // 현재 장착된 무기입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    TMap<int32, AGSFEquipmentBase*> EquippedEquipments;

public:
    UGSFEquipmentManager();

    /* ActorComponent */
    virtual void InitializeComponent() override;

    // 장비 혹은 무기를 추가할 수 있는지 확인합니다.
    UFUNCTION(BlueprintCallable)
    bool CanAddEquipment(TSubclassOf<AGSFEquipmentBase> EquipmentClass) const;

    // 장비 혹은 무기를 추가합니다.
    UFUNCTION(BlueprintCallable)
    bool AddEquipment(TSubclassOf<AGSFEquipmentBase> EquipmentClass);

    // 장착된 무기를 가져옵니다.
    UFUNCTION(BlueprintCallable)
    AGSFWeaponBase* GetWeapon(int32 Index);

    // 장착된 장비를 가져옵니다.
    UFUNCTION(BlueprintCallable)
    AGSFEquipmentBase* GetEquipment(int32 Index);

protected:
    UFUNCTION(BlueprintCallable)
    void AttachEquipmentToSocket(AGSFEquipmentBase* Equipment, FName SocketName);

private:
    void RegisterEquipment(AGSFEquipmentBase* Equipment);
    void RegisterWeapon(AGSFWeaponBase* Weapon);
    AGSFEquipmentBase* SpawnEquipment(TSubclassOf<AGSFEquipmentBase> EquipmentClass) const;
};
