// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GSFGameplayTags.h"
#include "GameFramework/Actor.h"
#include "GSFEquipmentBase.generated.h"

/**
 * GSFEquipmentComponent에서 사용하기 위한 장비 클래스입니다.
 */
UCLASS(Abstract)
class GASSURVIVALFRAMEWORK_API AGSFEquipmentBase : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE FGameplayTag GetEquipmentType() const { return GSFGameplayTags::Equipment::EquipmentTag; }
};
