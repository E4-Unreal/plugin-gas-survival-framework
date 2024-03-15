// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSFHitEffect.h"
#include "GSFHitEffect_Niagara.generated.h"

class UNiagaraSystem;

/**
 *
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFHitEffect_Niagara : public UGSFHitEffect
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    UNiagaraSystem* Niagara;

    UPROPERTY(EditDefaultsOnly)
    FVector Scale = FVector::One();

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const override;
};
