// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GSFWeaponContainer.generated.h"

class AGSFWeaponBase;

// TODO 박싱 언박싱 무시하고 AActor로 하는 것도 고려하는 중입니다.
// Enum을 무기 카테고리로 사용할 생각으로 작성한 클래스인데 GameplayTag를 사용하는 것이 더 좋을 것 같아서 보류되었습니다.
// 현재는 사용 예정이 없습니다만 나중에 다시 사용할 수 있으니 일단 놔둡니다.

/**
 * GSFEquipmentManager에서 무기 슬롯 종류에 따라 관리를 별도로 해주기 위해 슬롯 번호 관리를 위한 클래스입니다.
 * TMap<EquipmentType, UGSFWeaponContainer*> 이런 구조로 사용하려고 합니다.
 */
UCLASS(EditInlineNew, DefaultToInstanced)
class GASSURVIVALFRAMEWORK_API UGSFWeaponContainer : public UObject
{
    GENERATED_BODY()

    // 무기를 부착할 캐릭터 메시 소켓 이름 목록입니다. 목록 개수가 곧 최대 슬롯 개수가 됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<FName> SocketNames;

    // 장착 가능한 슬롯 번호 목록입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
    TArray<int32> AvailableIndices;

    // 현재 장착된 무기 오브젝트 목록입니다. 크기는 고정이며 null이 들어갈 수 있습니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
    TArray<TObjectPtr<AGSFWeaponBase>> EquippedWeapons;

public:
    virtual void PostInitProperties() override;

    /* API */
    UFUNCTION(BlueprintCallable)
    bool CanAdd(AGSFWeaponBase* Weapon) const { return !AvailableIndices.IsEmpty(); }

    UFUNCTION(BlueprintCallable)
    bool Add(AGSFWeaponBase* Weapon);

    UFUNCTION(BlueprintCallable)
    AGSFWeaponBase* Remove(int Index);
};
