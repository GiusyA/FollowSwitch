// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "MyUtils.h"

ASwitch::ASwitch()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

}

void ASwitch::UnRegister(AFollowSwitchCharacter* _character)
{
	UE_LOG(LogTemp, Warning, TEXT("character"))
	if (!_character)
		return;
	UE_LOG(LogTemp, Warning, TEXT("character IF"))
	characterGroup.Remove(_character);
	_character->SetCanBeDestroy(true);
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitch::SwitchPossession()
{

	AFollowSwitchCharacter* _pawn = Cast<AFollowSwitchCharacter>(PAWN);

	if (_pawn == characterGroup[charIndex])
	{
		UnPossess(_pawn);
	}
	else
	{
		Possess();
	}
}

void ASwitch::Possess()
{
	AFollowSwitchCharacter* _character = Cast<AFollowSwitchCharacter>(FPC->GetViewTarget());
	if (_character == characterGroup[charIndex])
	{
		FPC->Possess(_character);
		_character->SetIsPawn(true);
	}

}

void ASwitch::UnPossess(AFollowSwitchCharacter* _character)
{
	FPC->UnPossess();
	_character->SetIsPawn(false);
}

void ASwitch::IncrementSwitch()
{
	charIndex++;
	if (charIndex >= characterGroup.Num())
		charIndex = 0;
	onIncrement.Broadcast();
}

void ASwitch::Switch()
{
	if (!GetWorld()->GetFirstPlayerController() || characterGroup.Num() == 0)
		return;
	AFollowSwitchCharacter* _nextCharacter = characterGroup[charIndex];
	if (!_nextCharacter)
		return;
	GetWorld()->GetFirstPlayerController()->SetViewTarget(currentChar);
	currentChar = _nextCharacter;
	
}

void ASwitch::Init()
{
	onIncrement.AddDynamic(this, &ASwitch::Switch);
	if (!GetWorld()->GetFirstPlayerController())
		return;
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction(POSSESS, IE_Pressed, this, &ASwitch::SwitchPossession);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Switch", IE_Pressed, this, &ASwitch::IncrementSwitch);
	Switch();
}
