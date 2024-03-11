// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GSFHitEffectDefinition.h"

#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"


void UGSFHitEffectDefinition::SpawnHitEffect(const FHitResult& HitResult)
{
	// HitResult 유효성 검사
	if(!HitResult.bBlockingHit) return;

	// HitResult 분석
	const FVector_NetQuantize& ImpactPoint = HitResult.ImpactPoint;
	const FRotator& ImpactRotator = FRotationMatrix::MakeFromZ(HitResult.ImpactNormal).Rotator();
	UPrimitiveComponent* TargetComponent = HitResult.Component.Get();
    UPhysicalMaterial* PhysMaterial = HitResult.PhysMaterial.Get();

    // 적용할 이펙트 선택
    const FGSFHitEffectConfig& HitEffectConfig = HitEffectMap.Contains(PhysMaterial) ? HitEffectMap[PhysMaterial] : DefaultHitEffect;

	// 소리 재생
    SpawnSound(HitEffectConfig.SoundEffect, HitResult);

	// 이펙트 스폰
	SpawnSystem(HitEffectConfig.VisualEffect, HitResult);
}

void UGSFHitEffectDefinition::SpawnSound(const FGSFSoundConfig& SoundConfig, const FHitResult& HitResult)
{
    // null 검사
    if(SoundConfig.Sound == nullptr) return;

    // 소리 재생
    UGameplayStatics::PlaySoundAtLocation(
        HitResult.GetComponent(),
        SoundConfig.Sound,
        HitResult.ImpactPoint,
        FRotator::ZeroRotator
        );
}

void UGSFHitEffectDefinition::SpawnSystem(const FGSFVisualConfig& VisualConfig, const FHitResult& HitResult)
{
    // null 검사
    if(VisualConfig.Effect == nullptr) return;

    // HitResult 분석
    const FVector_NetQuantize& ImpactPoint = HitResult.ImpactPoint;
    const FRotator& ImpactRotator = FRotationMatrix::MakeFromZ(HitResult.ImpactNormal).Rotator();
    UPrimitiveComponent* TargetComponent = HitResult.GetComponent();
    UPhysicalMaterial* PhysMaterial = HitResult.PhysMaterial.Get();

    // 이펙트 스폰
    if(UParticleSystem* ParticleSystem = Cast<UParticleSystem>(VisualConfig.Effect))
    {
        UParticleSystemComponent* SpawnedSystem = UGameplayStatics::SpawnEmitterAttached(
            ParticleSystem,
            HitResult.GetComponent(),
            NAME_None,
            ImpactPoint,
            ImpactRotator,
            EAttachLocation::Type::KeepWorldPosition,
            true
            );

        if(SpawnedSystem)
            SpawnedSystem->SetWorldScale3D(VisualConfig.Scale);
    }
    else if(UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(VisualConfig.Effect))
    {
        UNiagaraComponent* SpawnedSystem = UNiagaraFunctionLibrary::SpawnSystemAttached(
            NiagaraSystem,
            TargetComponent,
            NAME_None,
            ImpactPoint,
            ImpactRotator,
            EAttachLocation::Type::KeepWorldPosition,
            true
            );

        if(SpawnedSystem)
            SpawnedSystem->SetWorldScale3D(VisualConfig.Scale);
    }
}
