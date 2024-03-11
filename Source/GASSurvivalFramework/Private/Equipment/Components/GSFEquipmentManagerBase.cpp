// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Components/GSFEquipmentManagerBase.h"

UGSFEquipmentManagerBase::UGSFEquipmentManagerBase()
{
    bWantsInitializeComponent = true;
    SetIsReplicated(true);
}

void UGSFEquipmentManagerBase::InitializeComponent()
{
    Super::InitializeComponent();

    SkeletalMesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
    bInitialized = SkeletalMesh != nullptr;
}
