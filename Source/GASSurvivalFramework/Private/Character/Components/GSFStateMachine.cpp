// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Components/GSFStateMachine.h"

#include "Character/States/GSFState_Combat.h"
#include "Character/States/GSFState_LockRotation.h"

UGSFStateMachine::UGSFStateMachine()
{
    StateClasses.Add(UGSFState_LockRotation::StaticClass());
    StateClasses.Add(UGSFState_Combat::StaticClass());
}
