// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GECharacter.h"
#include "GSFCharacterBase.generated.h"

/**
 * 모든 캐릭터의 기저 클래스입니다.
 *
 * 점프와 앉기 기능이 커스터마이징 되었습니다.
 * - 점프 중에는 앉을 수 없습니다.
 * - 앉은 상태에서 점프를 할 경우 앉은 상태를 해제한 후 점프를 진행합니다.
 *
 * GASExtension 플러그인의 AbilitySystem이 부착되어 있습니다.
 */

UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFCharacterBase : public AGECharacter
{
    GENERATED_BODY()

    // GetBaseAimRotation에서 사용하기 위한 리플리케이트된 Yaw
    UPROPERTY(Replicated)
    uint8 RemoteViewYaw;

public:
    AGSFCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

    virtual FRotator GetBaseAimRotation() const override;

private:
    void SetRemoteViewYaw(float NewRemoteViewYaw);
};
