// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/GSFEquipmentBase.h"
#include "GSFWeaponBase.generated.h"

UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFWeaponBase : public AGSFEquipmentBase
{
    GENERATED_BODY()

    /* 레퍼런스 */

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = true))
    TObjectPtr<UAnimInstance> CharacterAnimInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true, Categories = "Equipment.Weapon"))
    FGameplayTag WeaponType = GSFGameplayTags::Equipment::WeaponTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true, Categories = "Equipment.Slot"))
    FGameplayTag WeaponSlot = GSFGameplayTags::Equipment::PrimarySlotTag;

public:
    virtual FGameplayTag GetEquipmentType() const override { return WeaponType; }
    virtual FGameplayTag GetEquipmentSlot() const override { return WeaponSlot; }

    /* Actor */

    virtual void SetOwner(AActor* NewOwner) override;
    virtual void OnRep_Owner() override;

protected:
    /* 메서드 */
    UFUNCTION(BlueprintCallable)
    void PlayMontage(UAnimMontage* Montage);

    /* 가상 메서드 */

    UFUNCTION(BlueprintNativeEvent)
    void OnEquip();

    UFUNCTION(BlueprintNativeEvent)
    void OnUnEquip();

    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UAnimInstance* GetCharacterAnimInstance() const { return CharacterAnimInstance; }
};
