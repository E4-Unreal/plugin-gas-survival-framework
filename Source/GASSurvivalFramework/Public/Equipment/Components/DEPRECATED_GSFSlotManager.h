// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DEPRECATED_GSFSlotManager.generated.h"

/**
 * GSFWeaponManager 클래스의 서브 오브젝트로 사용하기 위해 작성되었으나 현재 사용하고 있지 않습니다.
 * 추후에 다시 활용할 수도 있을 것 같아 일단 코드는 남겨두었습니다.
 */
UCLASS(EditInlineNew, DefaultToInstanced, Deprecated)
class GASSURVIVALFRAMEWORK_API UDEPRECATED_GSFSlotManager : public UObject
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Transient)
    int32 SlotNum = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Transient)
    TArray<int32> AvailableIndices;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Transient)
    bool bDirty = false;

public:
    UFUNCTION(BlueprintCallable)
    void SetSlotNum(int32 InSlotNum);

    UFUNCTION(BlueprintCallable)
    bool Contains(int32 Index) const { return AvailableIndices.Contains(Index); }

    UFUNCTION(BlueprintCallable)
    bool Add(int32 Index);

    UFUNCTION(BlueprintPure)
    bool CanGet() const { return !AvailableIndices.IsEmpty(); }

    UFUNCTION(BlueprintCallable)
    int32 Get();
};
