﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GSFEquipmentManager.generated.h"


UCLASS(Abstract)
class GASSURVIVALFRAMEWORK_API UGSFEquipmentManager : public UActorComponent
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dependency", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
    bool bInitialized;

protected:
    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return SkeletalMesh; }

public:
    UGSFEquipmentManager();

    virtual void InitializeComponent() override;
};
