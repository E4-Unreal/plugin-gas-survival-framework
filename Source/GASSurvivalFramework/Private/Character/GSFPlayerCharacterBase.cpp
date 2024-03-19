// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/GSFPlayerCharacterBase.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Character/Components/GSFSpringArmComponent.h"

FName AGSFPlayerCharacterBase::SpringArmComponentName(TEXT("CameraBoom"));
FName AGSFPlayerCharacterBase::CameraComponentName(TEXT("FollowCamera"));

AGSFPlayerCharacterBase::AGSFPlayerCharacterBase(const FObjectInitializer& ObjectInitializer)
{
    /* 캐릭터 초기화 */
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    /* 서브 오브젝트 생성 및 할당 */
    CameraBoom = CreateDefaultSubobject<UGSFSpringArmComponent>(SpringArmComponentName);
    CameraBoom->SetupAttachment(RootComponent);

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(CameraComponentName);
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AGSFPlayerCharacterBase::GetTarget_Implementation(FVector& Target)
{
    const UWorld* World = GetWorld();
    if(World == nullptr) return;

    // 카메라를 기준으로 라인 트레이스를 위한 위치 계산
    const FTransform& CameraTransform = FollowCamera->GetComponentTransform();
    const FVector& TraceStart = CameraTransform.GetLocation();
    const FVector& TraceEnd = TraceStart + 100000.f * FollowCamera->GetForwardVector();
    FHitResult HitResult;

    // 라인 트레이스
    World->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility
        );

    Target = HitResult.bBlockingHit ? HitResult.Location : TraceEnd;
}
