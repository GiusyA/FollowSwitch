#include "Spawn.h"
#include "FollowSwitchCharacter.h"
#include "Switch.h"

ASpawn::ASpawn()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");


}

void ASpawn::BeginPlay()
{
	Super::BeginPlay();

}

void ASpawn::SpawnActor()
{
	
	if (memberList->CharacterGroupNum() < nbCharacterMax)
	{
		if (setSpawnPoint == nullptr)
		{
			AFollowSwitchCharacter* _character = GetWorld()->SpawnActor<AFollowSwitchCharacter>(character_BP, GetActorLocation(), FRotator::ZeroRotator);
			memberList->AddCharacterGroup(_character);
		}
		else
		{
			AFollowSwitchCharacter* _character = GetWorld()->SpawnActor<AFollowSwitchCharacter>(character_BP, setSpawnPoint->GetActorLocation(), FRotator::ZeroRotator);
			memberList->AddCharacterGroup(_character);
		}
	}
}

void ASpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebug();
	TimerSpawn(spawnTimer);
}

void ASpawn::TimerSpawn(float _timer)
{

	timer += GetWorld()->DeltaTimeSeconds;
	if (timer >= _timer && memberList->CharacterGroupNum() < nbCharacterMax)
	{
		SpawnActor();
		timer = 0;
	}

}

void ASpawn::DrawDebug()
{
	if (!useDrawDebug)
		return;
	DrawDebugSphere(GetWorld(), GetActorLocation(), 25, 60, FColor::Red, false, -1, 0, 0);
	if (!setSpawnPoint)
		return;
	DrawDebugLine(GetWorld(), GetActorLocation(), setSpawnPoint->GetActorLocation(), FColor::Red, false, -1, 0, 0);
}

