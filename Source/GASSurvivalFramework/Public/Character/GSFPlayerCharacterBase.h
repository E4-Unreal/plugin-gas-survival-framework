// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GSFCharacterBase.h"
#include "Weapon/Interface/AimingInterface.h"
#include "GSFPlayerCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 캐릭터 기본 조작 및 기본 설정이 정의된 기저 클래스입니다.
 */
UCLASS()
class GASSURVIVALFRAMEWORK_API AGSFPlayerCharacterBase : public AGSFCharacterBase, public IAimingInterface
{
	GENERATED_BODY()

public:
    /* SpringArm Component의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName SpringArmComponentName;

    /* Camera ComponentName의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName CameraComponentName;

private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

    /** Crouch Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> CrouchAction;

public:
	AGSFPlayerCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    /* Pawn */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    /* Actor */
    virtual void BeginPlay() override;

    /* 메서드 */

    // 향상된 입력 컴포넌트 설정
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent);

	// 캐릭터 이동
	virtual void Move(const FInputActionValue& Value);

	// 컨트롤러 회전
	virtual void Look(const FInputActionValue& Value);

    // 앉기 입력 이벤트 핸들링
    void OnCrouchActionStarted(const FInputActionValue& Value);

public:
	/* 컴포넌트 Getter */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
    /* AimingInterface */
    virtual void GetTarget_Implementation(FVector& Target) override;
};

