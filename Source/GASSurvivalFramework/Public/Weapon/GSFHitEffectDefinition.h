// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GSFHitEffectDefinition.generated.h"

class USoundCue;
class UFXSystemAsset;
class UMaterialInterface;

USTRUCT(Atomic, BlueprintType)
struct FGSFSoundConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundCue* Sound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VolumeMultiplier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PitchMultiplier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime = 0;
};

USTRUCT(Atomic, BlueprintType)
struct FGSFVisualConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UFXSystemAsset* Effect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Scale = FVector::One();
};

USTRUCT(Atomic, BlueprintType)
struct FGSFDecalConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInterface* DecalMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxSize = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinSize = 10.f;

    // 투영 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Depth = 10.f;
};

USTRUCT(Atomic, BlueprintType)
struct FGSFSplatterDecalConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGSFDecalConfig DecalConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseSplatter = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SplatterDistance = 300.f;
};

USTRUCT(Atomic, BlueprintType)
struct FGSFHitEffectConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGSFVisualConfig VisualEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGSFSoundConfig SoundEffect;

    // 피격 대상에 직접 스폰할 데칼
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGSFDecalConfig Decal;

    // 피격 대상 뒤쪽에 스폰할 데칼 (관통)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGSFSplatterDecalConfig SplatterDecal;
};

/*
 * 히트 스캔 방식의 총기나 근접 무기 등에서는 무기 자체에서 피격 판정이 이루어지기 때문에 직접 피격 효과를 스폰해야 하지만,
 * 총알처럼 발사체를 사용하는 경우에는 발사체에서 피격 효과를 스폰해야 합니다.
 *
 * 이처럼 서로 다른 클래스에서 동일한 방식으로 피격 효과를 스폰하기 위한 데이터 에셋입니다.
 */
UCLASS(BlueprintType)
class GASSURVIVALFRAMEWORK_API UGSFHitEffectDefinition : public UDataAsset
{
	GENERATED_BODY()

    // HitEffectMap에 등록되지 않은 경우 사용할 기본 피격 효과입니다.
	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FGSFHitEffectConfig DefaultHitEffect;

	// 피지컬 머터리얼에 따라 피격 효과를 다르게 적용하기 위한 설정입니다.
    UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
    TMap<TObjectPtr<UPhysicalMaterial>, FGSFHitEffectConfig> HitEffectMap;

public:
    // 피격 정보에 따라 적절한 피격 효과를 스폰합니다.
	UFUNCTION(BlueprintCallable)
	void SpawnHitEffect(const FHitResult& HitResult);

private:
    // SFX 스폰
    void SpawnSound(const FGSFSoundConfig& SoundConfig, const FHitResult& HitResult);

    // VFX 스폰
    void SpawnSystem(const FGSFVisualConfig& VisualConfig, const FHitResult& HitResult);

    // 데칼 스폰
    void SpawnDecal(const FGSFDecalConfig& DecalConfig, const FHitResult& HitResult);

    // 피격 대상 뒤쪽에 데칼 스폰
    void SpawnSplatterDecal(const FGSFSplatterDecalConfig& SplatterDecalConfig, const FHitResult& HitResult);
};
