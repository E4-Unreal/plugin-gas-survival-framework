// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Components/GSFEquipmentManager.h"

UGSFEquipmentManager::UGSFEquipmentManager()
{
    bWantsInitializeComponent = true;
}

void UGSFEquipmentManager::InitializeComponent()
{
    Super::InitializeComponent();

    SkeletalMesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
    bInitialized = SkeletalMesh != nullptr;
}
