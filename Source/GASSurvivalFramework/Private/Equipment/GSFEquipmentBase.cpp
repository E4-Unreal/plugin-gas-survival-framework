// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/GSFEquipmentBase.h"

AGSFEquipmentBase::AGSFEquipmentBase()
{
    SetReplicates(true);
}

void AGSFEquipmentBase::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGSFEquipmentBase::OnRep_Owner()
{
    Super::OnRep_Owner();

    if(GetOwner() == nullptr)
        OnUnEquip();
    else
        OnEquip();
}

void AGSFEquipmentBase::OnEquip_Implementation()
{
}

void AGSFEquipmentBase::OnUnEquip_Implementation()
{
}
