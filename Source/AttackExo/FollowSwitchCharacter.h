
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

	UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UPathComponent> pathComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
		bool isPawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		float speed = 100.0f;

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
	void FollowCurrentPath();
#pragma endregion CUSTOM_METHODS
};