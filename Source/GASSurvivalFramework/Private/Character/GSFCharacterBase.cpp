// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GSFCharacterBase.h"

#include "GEAbilitySystemBase.h"
#include "Character/GEState.h"
#include "Character/GEStateMachine.h"
#include "Character/Components/GSFCharacterMovement.h"
#include "Character/Components/GSFStateMachine.h"
#include "Components/CapsuleComponent.h"
#include "Equipment/Components/GSFEquipmentManager.h"

FName AGSFCharacterBase::AbilitySystemComponentName(TEXT("AbilitySystem"));
FName AGSFCharacterBase::EquipmentManagerName(TEXT("EquipmentManager"));
FName AGSFCharacterBase::StateMachineName(TEXT("StateMachine"));

AGSFCharacterBase::AGSFCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGSFCharacterMovement>(CharacterMovementComponentName))
{
    /* 서브 오브젝트 생성 */
    AbilitySystem = CreateDefaultSubobject<UGEAbilitySystemBase>(AbilitySystemComponentName); // GASExtension 플러그인 사용
    EquipmentManager = CreateDefaultSubobject<UGSFEquipmentManager>(EquipmentManagerName);
    StateMachine = CreateDefaultSubobject<UGSFStateMachine>(StateMachineName); // GASExtension 플러그인 사용

    // 캡슐 컴포넌트 초기화
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
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
