// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSFEquipmentBase.h"
#include "GSFArmorBase.generated.h"

UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFArmorBase : public AGSFEquipmentBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true, Categories = "Equipment.Armor"))
    FGameplayTag ArmorTag = GSFGameplayTags::Equipment::ArmorTag;

public:
    virtual FGameplayTag GetEquipmentType() const override { return ArmorTag; }
};
