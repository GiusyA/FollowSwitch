
#include "FollowSwitchCharacter.h"
#include "MyUtils.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	bUseControllerRotationYaw = true;
}

void AFollowSwitchCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AFollowSwitchCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DestroyItself(this);
	FollowCurrentPath();
}

void AFollowSwitchCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FORWARD, this, &AFollowSwitchCharacter::MoveForward);
	PlayerInputComponent->BindAxis(ROTATION, this, &AFollowSwitchCharacter::RotateYaw);
}
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
void AFollowSwitchCharacter::DestroyItself(AFollowSwitchCharacter* _character)
{
	if (!canBeDestroy)
		return;
	Destroy();
}

void AFollowSwitchCharacter::FollowCurrentPath()
{
	if (!pathComponent)
		return;

	if (!isPawn)
	{
		onMoveForward.Broadcast(1);

		FPathNodes _path = pathComponent->GetChosenPath();
		TArray<FVector> _nodes = _path.nodes;

		if (_path.currentNode == _nodes.Num())
		{
			onEndPath.Broadcast(this);
			return;
		}

		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), _nodes[_path.currentNode], DELTATIME, speed));
		SetActorRotation(FMath::Lerp(GetActorRotation(), UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _nodes[_path.currentNode]), DELTATIME));

		if (IsAtRange(_nodes[_path.currentNode]))
			pathComponent->SetCurrentNode(_path.currentNode + 1);
	}
}

bool AFollowSwitchCharacter::IsAtRange(const FVector& _location)
{
	return FVector::Distance(GetActorLocation(), _location) <= 5;
}

void AFollowSwitchCharacter::MoveForward(float _axis)
{
	AddMovementInput(GetActorForwardVector(), _axis * DELTATIME * (speed / 4.0f));
	onMoveForward.Broadcast(_axis);
}

void AFollowSwitchCharacter::RotateYaw(float _axis)
{
	AddControllerYawInput(_axis * DELTATIME * (speed / 4.0f));
}

void AFollowSwitchCharacter::Possess()
{
	isPawn = true;
	FPC->Possess(this);
}

void AFollowSwitchCharacter::UnPossess()
{
	isPawn = false;
	FPC->UnPossess();
}
#pragma endregion CUSTOM_METHODS