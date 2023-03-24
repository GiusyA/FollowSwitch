
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PathComponent.h"
#include "FollowSwitchCharacter.generated.h"

UCLASS()
class ATTACKEXO_API AFollowSwitchCharacter : public ACharacter
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndPath, AFollowSwitchCharacter*, _character);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveForward, float, _axis);

	UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UPathComponent> pathComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
		bool isPawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		float speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintCallable, BlueprintAssignable, meta = (AllowPrivateAccess))
		FOnEndPath onEndPath;

	UPROPERTY(EditAnywhere, BlueprintCallable, BlueprintAssignable, meta = (AllowPrivateAccess))
		FOnMoveForward onMoveForward;

#pragma region UE_METHODS
public:
	AFollowSwitchCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
private:
	UFUNCTION(BlueprintCallable) void DestroyItself(AFollowSwitchCharacter* _character);
	void FollowCurrentPath();
	UFUNCTION(BlueprintCallable) bool IsAtRange(const FVector& _location);
	void MoveForward(float _axis);
	void RotateYaw(float _axis);

public:
	FORCEINLINE void SetIsPawn(const bool& _value)
	{
		isPawn = _value;
	}
	FORCEINLINE FOnEndPath& OnEndPath()
	{
		return onEndPath;
	}
	FORCEINLINE FOnMoveForward& OnMoveForward()
	{
		return onMoveForward;
	}
#pragma endregion CUSTOM_METHODS
};