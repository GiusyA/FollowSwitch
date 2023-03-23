
#include "ProjectileActor.h"
#include "MyUtils.h"
#include "AttackComponent.h"

#pragma region UE_METHODS
AProjectileActor::AProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CREATE(USceneComponent, "Root");

	mesh = CREATE(UStaticMeshComponent, "Mesh");
	ATTACH_TO(mesh, RootComponent);
}

void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	onEndLife.AddDynamic(this, &AProjectileActor::DestroyProjectile);
}

void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateLifeTimer();
	Move();
}
#pragma endregion UE_METHODS

#pragma region CUSTOM_METHODS

void AProjectileActor::DestroyProjectile()
{
	Destroy();
}

void AProjectileActor::Move()
{
	AddActorLocalOffset(FVector(1, 0, 0) * DELTATIME * settings.speed);
}

void AProjectileActor::UpdateLifeTimer()
{
	settings.lifeTimer += DELTATIME;

	if (settings.lifeTimer >= settings.lifeSpan)
		onEndLife.Broadcast();
}
#pragma endregion CUSTOM_METHODS