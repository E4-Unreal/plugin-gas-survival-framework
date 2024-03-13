// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GSFCharacterBase.h"

#include "Character/Components/GSFCharacterMovement.h"
#include "Character/Components/GSFStateMachine.h"
#include "Components/CapsuleComponent.h"
#include "Equipment/Components/GSFEquipmentManager.h"
#include "Net/UnrealNetwork.h"

FName AGSFCharacterBase::EquipmentManagerName(TEXT("EquipmentManager"));

AGSFCharacterBase::AGSFCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.
        SetDefaultSubobjectClass<UGSFCharacterMovement>(CharacterMovementComponentName)
        .SetDefaultSubobjectClass<UGSFStateMachine>(StateMachineName)
        )
{
    /* 서브 오브젝트 생성 */
    EquipmentManager = CreateDefaultSubobject<UGSFEquipmentManager>(EquipmentManagerName);

    // 캡슐 컴포넌트 초기화
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // 호스트 플레이어가 없는 경우(렌더링되지 않는 경우)에도 스켈레탈 메시의 위차가 정확히 반영되기 위한 설정
    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AGSFCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(ThisClass, RemoteViewYaw, COND_SkipOwner);
}

void AGSFCharacterBase::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
    Super::PreReplication(ChangedPropertyTracker);

    if (GetLocalRole() == ROLE_Authority && GetController())
    {
        SetRemoteViewYaw(GetController()->GetControlRotation().Yaw);
    }
}

FRotator AGSFCharacterBase::GetBaseAimRotation() const
{
    // 지역 변수 정의
    FRotator BaseAimRotation = Super::GetBaseAimRotation();

    // 컨트롤러가 없는 경우 리플리케이트된 Yaw 값을 사용
    if(Controller == nullptr)
    {
        BaseAimRotation.Yaw = FRotator::DecompressAxisFromByte(RemoteViewYaw);
    }

    return BaseAimRotation;
}

bool AGSFCharacterBase::CanJumpInternal_Implementation() const
{
    // 앉은 상태에서도 점프가 가능합니다.
    return JumpIsAllowedInternal();
}

bool AGSFCharacterBase::CanCrouch() const
{
    // 점프 상태에서는 앉기가 불가능합니다.
    return !GetCharacterMovement()->IsFalling() && Super::CanCrouch();
}

void AGSFCharacterBase::SetRemoteViewYaw(float NewRemoteViewYaw)
{
    // Yaw를 1 바이트로 압축
    RemoteViewYaw = FRotator::CompressAxisToByte(NewRemoteViewYaw);
}
