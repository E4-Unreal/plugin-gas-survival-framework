﻿// Fill out your copyright notice in the Description page of Project Settings.

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
    bool IsValid() const { return SlotTag != FGameplayTag::EmptyTag; }

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

UCLASS(ClassGroup=(GASSurvivalFramework), meta=(BlueprintSpawnableComponent))
class GASSURVIVALFRAMEWORK_API UGSFEquipmentManager : public UGSFEquipmentManagerBase
{
    GENERATED_BODY()

    // 기본적으로 추가될 장비 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<AGSFEquipmentBase>> DefaultEquipments;

    // 선택 장비를 부착할 소켓 이름입니다. 선택 장비는 손에 쥐고 있을 잘비를 의미합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    FName HandSocketName = "weapon_r";

    // 사용 가능한 무기 슬롯 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<FEquipmentSlotConfig> EquipmentSlotConfigs;

    // 실제 인게임 내에서 사용하는 무기 슬롯 목록입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    TMap<FEquipmentSlot, TObjectPtr<AGSFEquipmentBase>> EquipmentSlots;

    // 손에 쥐고 있는 무기 슬롯입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient)
    FEquipmentSlot SelectedSlot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true), Transient, ReplicatedUsing = OnRep_SelectedEquipment)
    TObjectPtr<AGSFEquipmentBase> SelectedEquipment;

public:

    virtual void InitializeComponent() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

    // 손에 쥐고 있는 장비 (SelectedEquipment) 가져오기
    UFUNCTION(BlueprintPure)
    FORCEINLINE AGSFEquipmentBase* GetSelectedEquipment() const { return SelectedEquipment; }

    // 손에 쥐고 있는 장비를 집어넣습니다. 장비를 제거하는 것이 아닙니다.
    UFUNCTION(BlueprintCallable)
    void Deselect();

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsSelectedEquipmentExist() const { return SelectedSlot.IsValid() && SelectedEquipment != nullptr; }

    UFUNCTION(BlueprintCallable)
    void AttachEquipmentToSocket(AGSFEquipmentBase* Equipment, FName SocketName);

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

    // 기본 장비를 추가합니다.
    void AddDefaultEquipments();

    /* 리플리케이트 */

    UFUNCTION()
    void OnRep_SelectedEquipment(AGSFEquipmentBase* OldEquipment);
};
