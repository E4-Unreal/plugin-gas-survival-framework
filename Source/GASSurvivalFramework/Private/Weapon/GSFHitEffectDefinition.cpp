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

    // 데칼 스폰
    SpawnDecal(HitEffectConfig.Decal, HitResult);

    // Splatter 데칼 스폰
    SpawnSplatterDecal(HitEffectConfig.SplatterDecal, HitResult);
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

void UGSFHitEffectDefinition::SpawnDecal(const FGSFDecalConfig& DecalConfig, const FHitResult& HitResult)
{
    // null 검사
    if(DecalConfig.DecalMaterial == nullptr) return;

    // HitResult 분석
    const FVector_NetQuantize& ImpactPoint = HitResult.ImpactPoint;
    FRotator HitRotator = (-HitResult.ImpactNormal).Rotation();
    UPrimitiveComponent* TargetComponent = HitResult.GetComponent();
    const FName& HitBoneName = HitResult.BoneName;

    // 데칼 스폰 정보 생성
    const float RandomSize = FMath::RandRange(DecalConfig.MinSize, DecalConfig.MaxSize);
    const FVector DecalSize = FVector(DecalConfig.Depth, RandomSize, RandomSize);
    HitRotator.Add(0, 0, FMath::RandRange(0, 360));

    // 데칼 스폰
    UGameplayStatics::SpawnDecalAttached(
        DecalConfig.DecalMaterial,
        DecalSize,
        TargetComponent,
        HitBoneName,
        ImpactPoint,
        HitRotator,
        EAttachLocation::Type::KeepWorldPosition
        );
}

void UGSFHitEffectDefinition::SpawnSplatterDecal(const FGSFSplatterDecalConfig& SplatterDecalConfig,
    const FHitResult& HitResult)
{
    // 옵션 사용 여부 확인
    if(!SplatterDecalConfig.bUseSplatter) return;

    // 피격 대상으로부터 World 가져오기
    UWorld* World = HitResult.GetActor()->GetWorld();
    if(World == nullptr) return;

    /* 라인 트레이스 */

    // 피격 지점에서 추가 라인 트레이스
    const FVector& TraceStart = HitResult.ImpactPoint;
    const FVector Direction = (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal();
    const FVector TraceEnd = TraceStart + Direction * SplatterDecalConfig.SplatterDistance;

    // 피격 대상은 제외
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(HitResult.GetActor());

    // 라인 트레이스 실행
    FHitResult SplatterHitResult;
    World->LineTraceSingleByChannel(
        SplatterHitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        CollisionQueryParams
        );

    // Splatter 데칼 스폰
    SpawnDecal(SplatterDecalConfig.DecalConfig, SplatterHitResult);
}
