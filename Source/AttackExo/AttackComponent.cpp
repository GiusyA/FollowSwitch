
#include "AttackComponent.h"
#include "MyUtils.h"
#include "ProjectileActor.h"

#pragma region UE_METHODS
UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	owner->InputComponent->BindAction(bindName, EInputEvent::IE_Pressed, this, &UAttackComponent::LaunchAttack);
}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS
void UAttackComponent::LaunchAttack()
{
	if (!projectileRef)
		return;

	if (settings.useOwnerLocation)
		settings.attackSourceLocation = owner->GetActorLocation();

	//for (size_t axis = 0; axis < settings.numberOfAxes; axis++)
	//{
	//	for (size_t number = 0; number < settings.numberOfProjectilesOnAxis; number++)
	//	{
	//		AProjectileActor* _projectile = WORLD->SpawnActor<AProjectileActor>(projectileRef, settings.attackSourceLocation, FRotator(0, settings.firstAxisRotation, 0));

	//		if (!_projectile)
	//			return;

	//		_projectile->AddActorLocalOffset(FVector(settings.offsetFromSource + (number * settings.distanceBetweenProjectiles), 0, 0));
	//	}
	//	
	//	settings.firstAxisRotation += settings.angleBetweenAxes;
	//}

	float _rotation = settings.firstAxisRotation;

	for (size_t axis = 0; axis < settings.numberOfAxes; axis++)
	{
		for (size_t number = 0; number < settings.numberOfProjectilesOnAxis; number++)
		{
			const float _x = FMath::Cos(_rotation);
			const float _y = FMath::Sin(_rotation);

			AProjectileActor* _projectile = WORLD->SpawnActor<AProjectileActor>(projectileRef, settings.attackSourceLocation + FVector(_x, _y, 0), FRotator(0, _rotation, 0));

			_projectile->AddActorLocalOffset(FVector(settings.offsetFromSource + (number * settings.distanceBetweenProjectiles), 0, 0));
		}

		_rotation += settings.angleBetweenAxes;

		if (_rotation >= _rotation + 360)
			break;
	}
}
#pragma endregion CUSTOM_METHODS