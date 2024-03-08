// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GSFBlueprintFunctionLibrary.generated.h"

/**
 * GAS Survival Framework에서 사용하는 블루프린트 함수 라이브러리입니다.
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API UGSFBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Owner 위치에 액터를 스폰한 뒤 반환합니다.
    UFUNCTION(BlueprintCallable, Category = "GASSurvivalFramework")
    static AActor* SpawnActorOnOwner(TSubclassOf<AActor> ActorClass, AActor* Owner);

    // 스켈레탈 메시 소켓에 액터를 부착합니다.
    UFUNCTION(BlueprintCallable, Category = "GASSurvivalFramework")
    static bool AttachActorToSkeletalMeshSocket(AActor* Actor, USkeletalMeshComponent* SkeletalMesh, FName SocketName);
};
