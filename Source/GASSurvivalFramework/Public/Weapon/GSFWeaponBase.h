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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference|Weapon", meta = (AllowPrivateAccess = true))
    TObjectPtr<UAnimInstance> CharacterAnimInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Weapon", meta = (AllowPrivateAccess = true, Categories = "Equipment.Weapon"))
    FGameplayTag WeaponType = GSFGameplayTags::Equipment::WeaponTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Weapon", meta = (AllowPrivateAccess = true, Categories = "Equipment.Slot"))
    FGameplayTag WeaponSlot = GSFGameplayTags::Equipment::PrimarySlotTag;

public:
    /* GSFEquipmentBase */

    virtual FGameplayTag GetEquipmentType() const override { return WeaponType; }
    virtual FGameplayTag GetEquipmentSlot() const override { return WeaponSlot; }

protected:
    /* 메서드 */
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void PlayCharacterMontage(UAnimMontage* Montage);

    /* GSFEquipmentBase */

    virtual void OnEquip_Implementation() override;
    virtual void OnUnEquip_Implementation() override;

    /* Getter */

    UFUNCTION(BlueprintPure, Category = "Weapon")
    FORCEINLINE UAnimInstance* GetCharacterAnimInstance() const { return CharacterAnimInstance; }
};
