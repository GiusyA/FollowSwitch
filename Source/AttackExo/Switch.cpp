// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

ASwitch::ASwitch()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

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

void ASwitch::Posses()
{

}

void ASwitch::UnPosses()
{
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
	UE_LOG(LogTemp, Warning, TEXT("Switch"))
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
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Posses", IE_Pressed, this, &ASwitch::Posses);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Switch", IE_Pressed, this, &ASwitch::IncrementSwitch);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("UnPosses", IE_Pressed, this, &ASwitch::UnPosses);
	Switch();
}
