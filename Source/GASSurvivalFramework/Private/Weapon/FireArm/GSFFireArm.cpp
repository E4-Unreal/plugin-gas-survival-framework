// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon\FireArm\GSFFireArm.h"

#include "Net/UnrealNetwork.h"

AGSFFireArm::AGSFFireArm()
{
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
}

void AGSFFireArm::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 발사 간격 계산
    CalculateFireInterval();
}

void AGSFFireArm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, MaxAmmo);
    DOREPLIFETIME(ThisClass, CurrentAmmo);
}


void AGSFFireArm::Fire()
{
    // 발사 가능 여부 확인
    if(!CanFire()) return;

    // 서버에서 발사 실행
    ServerFire();
}

void AGSFFireArm::ServerFire_Implementation()
{
    // 발사 가능 여부 확인
    if(!CanFire()) return;

    // 발사 시간 기록
    LastFiredTime = GetCurrentTime();

    // 탄약 소비
    SpendAmmo();

    // 발사
    OnFire();

    // 멀티캐스트
    MulticastFire();
}

void AGSFFireArm::MulticastFire_Implementation()
{
    PlayAnimation(FireAnimation);
}

void AGSFFireArm::OnFire_Implementation()
{
    // TODO 자손 클래스에서 발사 로직 작성 (히트 스캔, 발사체)
}

void AGSFFireArm::Reload()
{
    // 장전 가능 여부 확인
    if(!CanReload()) return;

    // 서버에서 장전 실행
    ServerReload();
}

void AGSFFireArm::ServerReload_Implementation()
{
    // 장전 가능 여부 확인
    if(!CanReload()) return;
    bReloading = true;

    // 멀티캐스트
    MulticastReload();
}

void AGSFFireArm::MulticastReload_Implementation()
{
    PlayAnimation(ReloadAnimation);
}

void AGSFFireArm::FinishReloading()
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    bReloading = false;
}

void AGSFFireArm::SetMaxAmmo(int32 Value)
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // MaxAmmo 설정
    const int32 OldMaxAmmo = MaxAmmo;
    MaxAmmo = FMathf::Max(Value, 0);
    OnRep_MaxAmmo(OldMaxAmmo);
}

void AGSFFireArm::SetCurrentAmmo(int32 Value)
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // 재장전을 통해서만 설정이 가능합니다.
    if(!bReloading) return;

    // CurrentAmmo 설정
    const int32 OldCurrentAmmo = CurrentAmmo;
    CurrentAmmo = FMath::Clamp(Value, 0, MaxAmmo);
    OnRep_CurrentAmmo(OldCurrentAmmo);
}

void AGSFFireArm::PlayAnimation(UAnimSequence* Animation) const
{
    if(SkeletalMesh && Animation)
        SkeletalMesh->PlayAnimation(Animation, false);
}

bool AGSFFireArm::CanFire_Implementation()
{
    // 탄약 확인
    if(CurrentAmmo < AmmoToSpend) return false;

    // 아직 한 번도 발사하지 않은 경우
    if(LastFiredTime == 0) return true;

    // 발사 간격 확인
    return GetCurrentTime() - LastFiredTime >= FireInterval;
}

bool AGSFFireArm::CanReload_Implementation()
{
    // 이미 재장전중인 상태입니다.
    if(bReloading) return false;

    // 탄약이 가득 찬 경우에는 재장전을 할 필요가 없습니다.
    return CurrentAmmo < MaxAmmo;
}

void AGSFFireArm::SpendAmmo()
{
    SetCurrentAmmo(CurrentAmmo - FMath::Max(AmmoToSpend, 0));
}

float AGSFFireArm::GetCurrentTime() const
{
    if(const UWorld* World = GetWorld())
    {
        return World->GetTimeSeconds();
    }

    return -1.f;
}

FVector AGSFFireArm::GetMuzzleLocation() const
{
    return SkeletalMesh == nullptr ? GetActorLocation() : SkeletalMesh->GetSocketLocation(MuzzleSocketName);
}

void AGSFFireArm::OnRep_MaxAmmo(int32 OldCurrentAmmo)
{
    OnMaxAmmoValueChanged.Broadcast(MaxAmmo);
}

void AGSFFireArm::OnRep_CurrentAmmo(int32 OldCurrentAmmo)
{
    OnCurrentAmmoValueChanged.Broadcast(CurrentAmmo);
}
