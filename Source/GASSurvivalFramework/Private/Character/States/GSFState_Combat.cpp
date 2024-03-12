// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GSFState_Combat.h"

#include "AbilitySystemComponent.h"
#include "GSFGameplayTags.h"
#include "Character/GEStateMachine.h"

UGSFState_Combat::UGSFState_Combat()
{
    Triggers.AddTagFast(GSFGameplayTags::Action::AttackTag);
}

void UGSFState_Combat::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    if(GetTimerManager().IsTimerActive(ExitTimer))
    {
        // 만약 Exit Timer가 활성화된 상태라면 타이머를 종료합니다.
        GetTimerManager().ClearTimer(ExitTimer);
    }
    else
    {
        // Combat 태그를 부착합니다.
        GetStateMachine()->GetAbilitySystem()->AddLooseGameplayTag(GSFGameplayTags::State::CombatTag);
    }

}

void UGSFState_Combat::OnExit_Implementation()
{
    Super::OnExit_Implementation();

    // Duration 이후 Combat 태그를 제거합니다.
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this, &ThisClass::RemoveCombatTag);
    GetTimerManager().SetTimer(ExitTimer, TimerDelegate, Duration, false);
}

FTimerManager& UGSFState_Combat::GetTimerManager() const
{
    return GetStateMachine()->GetWorld()->GetTimerManager();
}

void UGSFState_Combat::RemoveCombatTag() const
{
    // Combat 태그를 제거합니다.
    GetStateMachine()->GetAbilitySystem()->RemoveLooseGameplayTag(GSFGameplayTags::State::CombatTag);
}
