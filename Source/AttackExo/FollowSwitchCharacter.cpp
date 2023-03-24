
#include "FollowSwitchCharacter.h"
#include "MyUtils.h"

#pragma region UE_METHODS
AFollowSwitchCharacter::AFollowSwitchCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CREATE(USpringArmComponent, "SpringArm");
	ATTACH_TO(springArm, RootComponent);

	camera = CREATE(UCameraComponent, "Camera");
	ATTACH_TO(camera, springArm);

	pathComponent = CREATE(UPathComponent, "PathComponent");
	AddOwnedComponent(pathComponent);
}

void AFollowSwitchCharacter::BeginPlay()
{
	Super::BeginPlay();

	//FPC->SetViewTarget(this);
}

void AFollowSwitchCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FollowCurrentPath();
}

void AFollowSwitchCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
void AFollowSwitchCharacter::FollowCurrentPath()
{
	if (!isPawn)
	{
		FPathNodes _path = pathComponent->GetChosenPath();
		TArray<FVector> _nodes = _path.nodes;

		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), _nodes[_path.currentNode], DELTATIME, speed));

		if (GetActorLocation() == _nodes[_path.currentNode])
			_path.currentNode++;

		if (_path.currentNode == _nodes.Num())
			return; //candestroy
	}
}
#pragma endregion CUSTOM_METHODS