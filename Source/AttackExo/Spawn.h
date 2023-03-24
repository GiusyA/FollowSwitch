
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawn.generated.h"

UCLASS()
class ATTACKEXO_API ASpawn : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> actor_BP = nullptr;
	UPROPERTY(EditAnywhere)
		bool useDrawDebug = true;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AActor> setSpawnPoint;

	UPROPERTY(EditAnywhere)
		TObjectPtr<class ASwitch> memberList;
	UPROPERTY(VisibleAnywhere)
		float timer = 0;
	UPROPERTY(EditAnywhere)
		float spawnTimer = 5;
	UPROPERTY()
		int nbCharacter = 0;
	UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1, UIMax = 10, ClampMax = 10))
		int nbCharacterMax = 4;
public:
	ASpawn();
	FORCEINLINE float GetnbCharacter() { return nbCharacter; }
	FORCEINLINE void SetnbCharacter(float _value) { nbCharacter = _value; }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void DrawDebug();
	void SpawnActor();
	void TimerSpawn(float _timer);


};
