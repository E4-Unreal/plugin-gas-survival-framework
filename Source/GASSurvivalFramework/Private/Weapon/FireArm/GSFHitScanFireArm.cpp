// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GSFHitScanFireArm.h"

#include "FunctionLibraries/GEFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Interface/AimingInterface.h"

void AGSFHitScanFireArm::OnFire_Implementation()
{
    if(GetOwner() && GetOwner()->GetClass()->ImplementsInterface(UAimingInterface::StaticClass()))
    {
        const UWorld* World = GetWorld();
        if(World == nullptr) return;

        /* 라인 트레이스 설정 */

        // 라인 트레이스 시작 위치
        const FVector& TraceStart = GetMuzzleLocation();

        // 발사 방향
        FVector Target;
        IAimingInterface::Execute_GetTarget(GetOwner(), Target);
        const FVector& Direction = (Target - TraceStart).GetSafeNormal();

        // 라인 트레이스 종료 위치
        const FVector& TraceEnd = TraceStart + MaxDistance * Direction;

        // 무기 및 소유자는 라인 트레이스 대상에서 제외
        FCollisionQueryParams CollisionQueryParams;
        CollisionQueryParams.AddIgnoredActor(this);
        CollisionQueryParams.AddIgnoredActor(GetOwner());

        // 라인 트레이스 실행
        FHitResult HitResult;
        World->LineTraceSingleByChannel(
            HitResult,
            TraceStart,
            TraceEnd,
            ECC_Visibility,
            CollisionQueryParams
            );

        // 히트 이벤트 처리
        OnHit(HitResult);
    }
}

void AGSFHitScanFireArm::OnHit(const FHitResult& HitResult)
{
    // 서버에서만 실행 가능합니다.
    if(!HasAuthority()) return;

    // GE 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetInstigator(), HitResult.GetActor());

    // 멀티캐스트
    OnMulticastHit(HitResult);
}

void AGSFHitScanFireArm::OnMulticastHit_Implementation(const FHitResult& HitResult)
{
    UGameplayStatics::SpawnEmitterAttached(
            HitEffect,
            HitResult.GetComponent(),
            NAME_None,
            HitResult.ImpactPoint,
            HitResult.ImpactNormal.ToOrientationRotator(),
            EAttachLocation::Type::KeepWorldPosition,
            true
            );
}
