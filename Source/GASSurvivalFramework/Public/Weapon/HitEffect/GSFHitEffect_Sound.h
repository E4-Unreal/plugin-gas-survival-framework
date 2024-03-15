// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/HitEffect/GSFHitEffect.h"
#include "GSFHitEffect_Sound.generated.h"

/**
 *
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFHitEffect_Sound : public UGSFHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    USoundCue* Sound;

    UPROPERTY(EditDefaultsOnly)
    float VolumeMultiplier = 1;

    UPROPERTY(EditDefaultsOnly)
    float PitchMultiplier = 1;

    UPROPERTY(EditDefaultsOnly)
    float StartTime = 0;

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
