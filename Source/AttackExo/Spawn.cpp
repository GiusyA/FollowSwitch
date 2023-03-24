#include "Spawn.h"
#include "FollowSwitchCharacter.h"
#include "Switch.h"
#include "MyUtils.h"
#include "Kismet/KismetMathLibrary.h"

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
	else if (timer >= _timer && nbCharacter >= nbCharacterMax)
		timer = 0;

}

void ASpawn::DrawDebug()
{
	if (!useDrawDebug)
		return;
	DrawDebugSphere(GetWorld(), GetActorLocation(), 25, 60, FColor::Cyan, false, -1, 0, 0);
	FColor _color = UKismetMathLibrary::LinearColorLerp(FColor::Red, FColor::Green, timer / spawnTimer).ToFColor(false);
	DRAW_BOX(GetActorLocation() + FVector(0, 0, 100), FVector(3) * timer, _color, 2);
	if (!setSpawnPoint)
		return;
	DrawDebugLine(GetWorld(), GetActorLocation(), setSpawnPoint->GetActorLocation(), FColor::Cyan, false, -1, 0, 0);
}