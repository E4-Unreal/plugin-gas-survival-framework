// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/GSFWeaponContainer.h"

void UGSFWeaponContainer::PostInitProperties()
{
    UObject::PostInitProperties();

    // 슬롯 개수 구하기
    const int32 SlotNum = SocketNames.Num();

    // 사용 가능한 슬롯 목록 초기화
    AvailableIndices.Reserve(SlotNum);
    for(int i = 0; i < SlotNum; i++)
    {
        AvailableIndices.Add(i);
    }

    // 장착된 무기 오브젝트 목록 초기화
    EquippedWeapons.Init(nullptr, SlotNum);
}

bool UGSFWeaponContainer::Add(AGSFWeaponBase* Weapon)
{
    // 남은 슬롯 확인
    if(Weapon == nullptr || !CanAdd(Weapon)) return false;

    // 내림차순 정렬
    AvailableIndices.Sort([](const int32& A, const int32& B)
    {
        return A > B;
    });

    // 가장 작은 인덱스 가져오기
    const int32 AvailableIndex = AvailableIndices.Pop(false);

    // 무기 추가
    EquippedWeapons.EmplaceAt(AvailableIndex);

    return true;
}

AGSFWeaponBase* UGSFWeaponContainer::Remove(int Index)
{
    // Index 유효성 검사
    if(EquippedWeapons.Num() > Index) return nullptr;

    // 해당 슬롯에 존재하는 무기 가져오기
    const auto Weapon = EquippedWeapons[Index];

    // 슬롯에 무기가 존재하지 않는 경우
    if(Weapon == nullptr) return nullptr;

    // 슬롯에서 무기 제거 및 반환 (사용 가능한 슬롯 번호에 추가)
    EquippedWeapons[Index] = nullptr;
    AvailableIndices.Emplace(Index);

    return Weapon;
}
