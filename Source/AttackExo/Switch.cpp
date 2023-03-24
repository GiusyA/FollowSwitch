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
	if (!_character)
		return;
	characterGroup.Remove(_character);
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (onCamera)
	{
		if (!camera)
			return;

		FPC->SetViewTarget(camera);
	}
}

void ASwitch::SwitchPossession()
{

	AFollowSwitchCharacter* _pawn = Cast<AFollowSwitchCharacter>(PAWN);

	if (_pawn == currentChar)
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
	FPC->Possess(currentChar);
	currentChar->SetIsPawn(true);
}

void ASwitch::UnPossess(AFollowSwitchCharacter* _character)
{
	FPC->UnPossess();
	_character->SetIsPawn(false);
	onCamera = true;
}

void ASwitch::DecrementSwitch()
{
	charIndex--;
	if (charIndex < 0)
		charIndex = CharacterGroupNum() - 1;
	onDecrement.Broadcast();
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
	onCamera = false;

	if (!GetWorld()->GetFirstPlayerController() || characterGroup.Num() == 0)
		return;
	AFollowSwitchCharacter* _nextCharacter = characterGroup[charIndex];

	if (!_nextCharacter)
		return;
	currentChar = !currentChar ? characterGroup[0] : currentChar;
	GetWorld()->GetFirstPlayerController()->SetViewTarget(currentChar);
	currentChar = _nextCharacter;
	
}

void ASwitch::Init()
{
	onIncrement.AddDynamic(this, &ASwitch::Switch);
	onDecrement.AddDynamic(this, &ASwitch::Switch);
	if (!GetWorld()->GetFirstPlayerController())
		return;
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction(POSSESS, IE_Pressed, this, &ASwitch::SwitchPossession);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction(SWITCH_UP, IE_Pressed, this, &ASwitch::IncrementSwitch);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction(SWITCH_DOWN, IE_Pressed, this, &ASwitch::DecrementSwitch);
}
