// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSFEquipmentBase.h"
#include "GSFWeaponBase.generated.h"

UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFWeaponBase : public AGSFEquipmentBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true, Categories = "Equipment.Weapon"))
    FGameplayTag WeaponTag = GSFGameplayTags::Equipment::WeaponTag;

public:
    virtual FGameplayTag GetEquipmentType() const override { return WeaponTag; };
};
