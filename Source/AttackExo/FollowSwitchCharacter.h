
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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndPath);

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
	UFUNCTION(BlueprintCallable) void DestroyItself();
	void FollowCurrentPath();
	UFUNCTION(BlueprintCallable) bool IsAtRange(const FVector& _location);
	void MoveForward(float _axis);
	void RotateYaw(float _axis);

public:
	void Possess(); //TODO dans l'idéal à mettre dans le switcher grâce au getter en dessous
	void UnPossess();
	FORCEINLINE void SetIsPawn(const bool& _value)
	{
		isPawn = _value;
	}
	FORCEINLINE FOnEndPath& OnEndPath()
	{
		return onEndPath;
	}
#pragma endregion CUSTOM_METHODS
};