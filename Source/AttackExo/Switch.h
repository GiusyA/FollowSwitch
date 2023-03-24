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
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIncrement);
	UPROPERTY(VisibleAnywhere)
		TArray<AFollowSwitchCharacter*> characterGroup;
	UPROPERTY()
		TObjectPtr<AFollowSwitchCharacter> currentChar = nullptr;
	UPROPERTY()
		TObjectPtr<AController> fpc = nullptr;
	UPROPERTY()
		int charIndex = 0;
	FOnIncrement onIncrement;
public:	
	ASwitch();
	FORCEINLINE FOnIncrement& OnIncrement() { return onIncrement; }
	FORCEINLINE TArray<AFollowSwitchCharacter*> GetCharacterGroup() { return characterGroup; }
	FORCEINLINE float CharacterGroupNum() { return characterGroup.Num(); }
	FORCEINLINE void AddCharacterGroup(AFollowSwitchCharacter* _value) { characterGroup.Add(_value); }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Posses();
	void UnPosses(AFollowSwitchCharacter* _character);
	void IncrementSwitch();
	UFUNCTION() void Switch();
	void SwitchPossession();
	void Init();
};
