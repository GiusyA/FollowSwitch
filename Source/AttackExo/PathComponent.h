
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathComponent.generated.h"

USTRUCT(BlueprintType)
struct FPathNodes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Nodes", BlueprintReadWrite)
		TArray<FVector> nodes;

	int currentNode = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATTACKEXO_API UPathComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
		TArray<FPathNodes> paths;

	int chosenPathIndex = 0;
	FVector ownerStartLocation = FVector(0);

#pragma region UE_METHODS
public:	
	UPathComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion UE_METHODS
		
#pragma region CUSTOM_METHODS
private:
	void DrawDebugChosenPath();
	void InitChosenPathIndex();
	void InitPaths();

public:
	FORCEINLINE void SetCurrentNode(const int& _value)
	{
		paths[chosenPathIndex].currentNode = _value;
	}
	FORCEINLINE FPathNodes GetChosenPath() const
	{
		return paths[chosenPathIndex];
	}
#pragma endregion CUSTOM_METHODS
};