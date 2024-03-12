// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GSFState_Dead.h"

#include "GSFGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGSFState_Dead::UGSFState_Dead()
{
    Triggers.AddTagFast(GSFGameplayTags::State::DeadTag);
}

void UGSFState_Dead::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    // 움직임 비활성화
    GetCharacter()->GetCharacterMovement()->DisableMovement();
    GetCharacter()->GetCharacterMovement()->StopMovementImmediately();

    // 스켈레탈 메시 콜리전 활성화
    GetCharacter()->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // 캡슐 컴포넌트 콜리전 비활성화
    GetCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UGSFState_Dead::OnExit_Implementation()
{
    Super::OnExit_Implementation();

    // 움직임 활성화
    GetCharacter()->GetCharacterMovement()->SetDefaultMovementMode();

    // 스켈레탈 메시 콜리전 활성화
    GetCharacter()->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    // 캡슐 컴포넌트 콜리전 활성화
    GetCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
