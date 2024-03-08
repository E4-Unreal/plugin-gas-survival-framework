// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GSFEquipmentManagerBase.h"
#include "GSFEquipmentManager.generated.h"

class AGSFEquipmentBase;

USTRUCT(Atomic, BlueprintType)
struct FEquipmentSlotConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Equipment.Slot"))
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> SocketNames;
};

USTRUCT(Atomic, BlueprintType)
struct FEquipmentSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

    // 기본 구조체
    static const FEquipmentSlot EmptySlot;

    // 생성자
    FEquipmentSlot(){}

    FEquipmentSlot(FGameplayTag InSlotTag, int32 InIndex, FName InSocketName = NAME_None)
    {
        SlotTag = InSlotTag;
        Index = InIndex;
        SocketName = InSocketName;
    }

    /* 쿼리 */

    bool IsNotValid() const { return !IsValid(); }
    bool IsValid() const { return SlotTag == FGameplayTag::EmptyTag; }

    /* 연산자 오버로딩 */

    // 기본

    bool operator==(const FEquipmentSlot& Other) const
    {
        return Equals(Other);
    }

    bool operator!=(const FEquipmentSlot& Other) const
    {
        return !operator==(Other);
    }

    bool Equals(const FEquipmentSlot& Other) const
    {
        return SlotTag == Other.SlotTag && Index == Other.Index;
    }

    FORCEINLINE friend uint32 GetTypeHash(const FEquipmentSlot& Target)
    {
        return FCrc::MemCrc32(&Target, sizeof(FEquipmentSlot));
    }

    // 게임플레이 태그

    bool operator==(const FGameplayTag& OtherTag) const
    {
        return SlotTag == OtherTag;
    }
};

// TODO 무기 선택 기능 구현, 선택 가능 장비 슬롯 (게임플레이 태그) 설정, 손 슬롯 설정

UCLASS(ClassGroup=(GASSurvivalFramework), meta=(BlueprintSpawnableComponent))
class GASSURVIVALFRAMEWORK_API UGSFEquipmentManager : public UGSFEquipmentManagerBase
{
    GENERATED_BODY()

    // 사용 가능한 무기 슬롯 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<FEquipmentSlotConfig> EquipmentSlotConfigs;

    // 실제 인게임 내에서 사용하는 무기 슬롯 목록입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    TMap<FEquipmentSlot, TObjectPtr<AGSFEquipmentBase>> EquipmentSlots;

    // 손에 쥐고 있는 무기 슬롯입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    FEquipmentSlot SelectedSlot;

public:

    virtual void InitializeComponent() override;

    UFUNCTION(BlueprintCallable)
    bool AddEquipment(TSubclassOf<AGSFEquipmentBase> WeaponClass);

    UFUNCTION(BlueprintCallable)
    void RemoveEquipment(FGameplayTag Slot, int32 Index);

    UFUNCTION(BlueprintCallable)
    void SelectEquipment(FGameplayTag Slot, int32 Index);

    UFUNCTION(BlueprintCallable)
    bool IsEquipmentExist(FGameplayTag Slot, int32 Index) const;

    UFUNCTION(BlueprintCallable)
    bool IsEquipmentSlotExist(FGameplayTag Slot, int32 Index) const;

    UFUNCTION(BlueprintCallable)
    AGSFEquipmentBase* GetEquipment(FGameplayTag Slot, int32 Index) const;

    UFUNCTION(BlueprintCallable)
    void ClearEquipmentSlot(FGameplayTag Slot, int32 Index);

    /* Query */

    UFUNCTION(BlueprintCallable)
    bool CanAddEquipment(TSubclassOf<AGSFEquipmentBase> WeaponClass) const;

    UFUNCTION(BlueprintCallable)
    bool IsSlotAvailable(const FGameplayTag& WeaponSlot) const;

    UFUNCTION(BlueprintCallable)
    const FEquipmentSlot& GetAvailableSlot(const FGameplayTag& WeaponSlot) const;

private:
    // AvailableSlots로부터 EquipmentSlots를 생성합니다.
    void CreateEquipmentSlots();
};
