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

void AGSFPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// 입력 매핑 컨텍스트 추가
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AGSFPlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupEnhancedInputComponent(Cast<UEnhancedInputComponent>(PlayerInputComponent));
}

void AGSFPlayerCharacterBase::SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
    // null 검사
    if(EnhancedInputComponent == nullptr) return;

    // 캐릭터 점프
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

    // 캐릭터 이동
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGSFPlayerCharacterBase::Move);

    // 카메라 회전
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGSFPlayerCharacterBase::Look);

    // 캐릭터 앉기
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::OnCrouchActionStarted);
}

void AGSFPlayerCharacterBase::Move(const FInputActionValue& Value)
{
    // 컨트롤러만 사용할 수 있는 메서드입니다.
    if(Controller == nullptr) return;

	// 입력값 가져오기
	const FVector2D MovementVector = Value.Get<FVector2D>();

    // 회전값 가져오기
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // 이동 방향 계산
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // 이동 입력
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);

    // 좌우 반복 뛰기 시 180도로 회전하는 오류 방지
    if(FMath::IsNearlyZero(MovementVector.Y) && !FMath::IsNearlyZero(MovementVector.X))
    {
        AddMovementInput(ForwardDirection, 0.0001f);
    }
}

void AGSFPlayerCharacterBase::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGSFPlayerCharacterBase::OnCrouchActionStarted(const FInputActionValue& Value)
{
    if(bIsCrouched)
        UnCrouch();
    else
        Crouch();
}
