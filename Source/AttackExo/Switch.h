// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowSwitchCharacter.h"
#include "Switch.generated.h"

UCLASS()
class ATTACKEXO_API ASwitch : public AActor
{
	GENERATED_BODY()
	UPROPERTY()
		TArray<AFollowSwitchCharacter*> characterGroup;
	UPROPERTY()
		TObjectPtr<AFollowSwitchCharacter> currentChar = nullptr;
	UPROPERTY()
		TObjectPtr<AController> fpc = nullptr;
public:	
	ASwitch();
	FORCEINLINE TArray<AFollowSwitchCharacter*> GetCharacterGroup() { return characterGroup; }
	FORCEINLINE float CharacterGroupNum() { return characterGroup.Num(); }
	FORCEINLINE void AddCharacterGroup(AFollowSwitchCharacter* _value) { characterGroup.Add(_value); }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Posses();
	void UnPosses();
	void Switch();
	void Init();
};
