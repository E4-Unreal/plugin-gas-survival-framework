// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GSFCharacterBase.h"

#include "Character/GSFCharacterMovement.h"

AGSFCharacterBase::AGSFCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGSFCharacterMovement>(CharacterMovementComponentName))
{

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
