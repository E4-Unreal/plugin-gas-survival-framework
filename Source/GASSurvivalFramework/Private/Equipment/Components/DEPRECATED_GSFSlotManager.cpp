// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment\Components\DEPRECATED_GSFSlotManager.h"

void UDEPRECATED_GSFSlotManager::SetSlotNum(int32 InSlotNum)
{
    SlotNum = InSlotNum;

    AvailableIndices.Init(0, SlotNum);
    for(int i = 0; i < SlotNum; i++)
    {
        AvailableIndices[i] = i;
    }
}

bool UDEPRECATED_GSFSlotManager::Add(int32 Index)
{
    if(Contains(Index)) return false;

    AvailableIndices.Add(Index);
    bDirty = true;

    return true;
}

int32 UDEPRECATED_GSFSlotManager::Get()
{
    if(bDirty)
    {
        AvailableIndices.Sort([](const int32& A, const int32& B){ return A > B; });
        bDirty = false;
    }

    return AvailableIndices.Pop();
}


