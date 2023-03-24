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
	if (memberList)
		nbCharacter = memberList->CharacterGroupNum();


	if (nbCharacter < nbCharacterMax)
	{
		if (setSpawnPoint == nullptr)
		{
			AActor* _actor = GetWorld()->SpawnActor<AActor>(actor_BP, GetActorLocation(), FRotator::ZeroRotator);

			if (memberList)
			{
				AFollowSwitchCharacter* _character = Cast<AFollowSwitchCharacter>(_actor);

				if (_character)
					memberList->AddCharacterGroup(_character);
			}
			else
				nbCharacter++;
		}
		else
		{
			AActor* _actor = GetWorld()->SpawnActor<AActor>(actor_BP, setSpawnPoint->GetActorLocation(), FRotator::ZeroRotator);

			if (memberList)
			{
				AFollowSwitchCharacter* _character = Cast<AFollowSwitchCharacter>(_actor);

				if (_character)
					memberList->AddCharacterGroup(_character);
			}
			else
				nbCharacter++;
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
	if (timer >= _timer && nbCharacter < nbCharacterMax)
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