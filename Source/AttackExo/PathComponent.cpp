
#include "PathComponent.h"
#include "MyUtils.h"
#include "FollowSwitchCharacter.h"

#pragma region UE_METHODS
UPathComponent::UPathComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPathComponent::BeginPlay()
{
	Super::BeginPlay();

	InitPaths(); //temporaire parce que c'est chiant quand ça casse
	InitChosenPathIndex();
}

void UPathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugChosenPath();
}
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
void UPathComponent::DrawDebugChosenPath()
{
	if (paths.IsEmpty())
		return;

	const FVector _ownerLocation = OWNER->GetActorLocation();
	const FVector _ownerXY = FVector(_ownerLocation.X, _ownerLocation.Y, 0);

	DRAW_SPHERE(_ownerXY, 10, 5, FColor::Red, 2);
	TArray<FVector> _nodes = paths[chosenPathIndex].nodes;

	for (size_t i = 0; i < _nodes.Num(); i++)
	{
		if (i == 0)
			DRAW_LINE(_ownerXY, _nodes[i], FColor::Red, 2);

		if (i != (_nodes.Num() - 1))
			DRAW_LINE(_nodes[i], _nodes[i + 1], FColor::Red, 2);

		DRAW_SPHERE(_nodes[i], 10, 5, FColor::Red, 2);
	}
}

void UPathComponent::InitChosenPathIndex()
{
	if (!paths.IsEmpty())
	{
		chosenPathIndex = FMath::RandRange(0, paths.Num() - 1);

		const FVector _ownerLocation = OWNER->GetActorLocation();
		const FVector _ownerXY = FVector(_ownerLocation.X, _ownerLocation.Y, 0);

		for (size_t i = 0; i < paths.Num(); i++)
		{
			TArray<FVector> _nodes = paths[i].nodes;

			for (size_t y = 0; y < _nodes.Num(); y++)
				_nodes[y] = _ownerXY + _nodes[y];
		}
	}
}

void UPathComponent::InitPaths()
{
	FPathNodes _firstPath;
	_firstPath.nodes.Add(FVector(500, 100, 0));
	_firstPath.nodes.Add(FVector(1000, 0, 0));
	_firstPath.nodes.Add(FVector(1500, -100, 0));
	paths.Add(_firstPath);

	FPathNodes _secondPath;
	_secondPath.nodes.Add(FVector(100, 500, 0));
	_secondPath.nodes.Add(FVector(0, 1000, 0));
	_secondPath.nodes.Add(FVector(-100, 1500, 0));
	paths.Add(_secondPath);

	FPathNodes _thirdPath;
	_thirdPath.nodes.Add(FVector(100, -500, 0));
	_thirdPath.nodes.Add(FVector(0, -1000, 0));
	_thirdPath.nodes.Add(FVector(-100, -1500, 0));
	paths.Add(_thirdPath);
}
#pragma endregion CUSTOM_METHODS