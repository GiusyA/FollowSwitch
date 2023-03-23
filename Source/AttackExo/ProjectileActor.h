
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

USTRUCT(BlueprintType)
struct FProjectileSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.0f, ClampMin = 0.0f))
		float speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector spawnLocation = FVector(0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator spawnRotation = FRotator(0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.1f, ClampMin = 0.1f))
		float lifeSpan = 3.0f;

	UPROPERTY(BlueprintReadOnly)
		float lifeTimer = 0.0f;

	FORCEINLINE void SetSpawnLocation(const FVector& _location)
	{
		spawnLocation = _location;
	}

	FORCEINLINE void SetSpawnRotation(const FRotator& _rotation)
	{
		spawnRotation = _rotation;
	}

	FORCEINLINE void SetSpawnLocationRotation(const FVector& _location, const FRotator& _rotation)
	{
		SetSpawnLocation(_location);
		SetSpawnRotation(_rotation);
	}
};

UCLASS()
class ATTACKEXO_API AProjectileActor : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndLife);

	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		FProjectileSettings settings;

	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable, meta = (AllowPrivateAccess))
		FOnEndLife onEndLife;
	
#pragma region UE_METHODS
public:	
	AProjectileActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
private:
	UFUNCTION(BlueprintCallable) void DestroyProjectile();
	void Move();
	void UpdateLifeTimer();

public:
	FORCEINLINE FOnEndLife& OnEndLife()
	{
		return onEndLife;
	}
#pragma endregion CUSTOM_METHODS
};