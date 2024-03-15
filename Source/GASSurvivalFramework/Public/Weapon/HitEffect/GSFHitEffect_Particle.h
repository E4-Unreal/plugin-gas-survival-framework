// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSFHitEffect.h"
#include "GSFHitEffect_Particle.generated.h"

/**
 *
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFHitEffect_Particle : public UGSFHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* ParticleSystem;

    UPROPERTY(EditDefaultsOnly)
    FVector Scale = FVector::One();

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
