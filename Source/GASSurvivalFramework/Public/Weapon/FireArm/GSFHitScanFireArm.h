﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSFFireArm.h"
#include "GSFHitScanFireArm.generated.h"

class UGSFHitEffectDefinition;
class UGameplayEffect;

UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFHitScanFireArm : public AGSFFireArm
{
    GENERATED_BODY()

    // 피격 대상에게 적용할 GE 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

    // 라인 트레이스의 최대 거리입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    float MaxDistance = 100000.f;

    // 피격 효과
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    UGSFHitEffectDefinition* HitEffect;

protected:
    virtual void OnFire_Implementation() override;

    virtual void OnHit(const FHitResult& HitResult);

    UFUNCTION(NetMulticast, Reliable)
    void OnMulticastHit(const FHitResult& HitResult);
};
