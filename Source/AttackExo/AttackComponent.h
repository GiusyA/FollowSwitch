
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

USTRUCT(BlueprintType)
struct FAttackComponentSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, ClampMin = 0))
		int numberOfAxes = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float firstAxisRotation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, ClampMin = 0))
		int numberOfProjectilesOnAxis = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.0f, ClampMin = 0.0f))
		float distanceBetweenProjectiles = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1.0f, ClampMin = 1.0f))
		float angleBetweenAxes = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool useOwnerLocation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!useOwnerLocation"))
		FVector attackSourceLocation = FVector(0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.0f, ClampMin = 0.0f))
		float offsetFromSource = 50.0f;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATTACKEXO_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FName bindName = "STARFISH";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		FAttackComponentSettings settings;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectileActor> projectileRef = nullptr;

	UPROPERTY()
		TObjectPtr<AActor> owner = nullptr;

#pragma region UE_METHODS
public:	
	UAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
private:
	void LaunchAttack();
#pragma endregion CUSTOM_METHODS
};