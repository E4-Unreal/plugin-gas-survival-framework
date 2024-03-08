// Fill out your copyright notice in the Description page of Project Settings.


#include "GSFBlueprintFunctionLibrary.h"

AActor* UGSFBlueprintFunctionLibrary::SpawnActorOnOwner(TSubclassOf<AActor> ActorClass, AActor* Owner)
{
    // 월드 가져오기
    UWorld* World = Owner->GetWorld();

    // null 검사
    if(World == nullptr || ActorClass == nullptr) return nullptr;

    // Owner 및 Instigator 설정
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.Owner = Owner;
    ActorSpawnParameters.Instigator = Owner->GetInstigator();

    // Owner 위치에 액터 스폰
    const FVector SpawnLocation = Owner->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor(ActorClass, &SpawnLocation, &FRotator::ZeroRotator, ActorSpawnParameters);

    return SpawnedActor;
}

bool UGSFBlueprintFunctionLibrary::AttachActorToSkeletalMeshSocket(AActor* Actor, USkeletalMeshComponent* SkeletalMesh,
    FName SocketName)
{
    // 유효성 검사
    if(Actor == nullptr || SkeletalMesh == nullptr || SocketName == NAME_None) return false;

    // 소켓 존재 여부 검사
    if(SkeletalMesh->GetSocketByName(SocketName) == nullptr) return false;

    // 액터를 스켈레탈 메시 소켓에 부착
    Actor->AttachToComponent(SkeletalMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);

    return true;
}
