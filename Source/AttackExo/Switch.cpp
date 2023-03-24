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

void ASwitch::Switch()
{
	if (!GetWorld()->GetFirstPlayerController() || characterGroup.Num() == 0)
		return;
}

void ASwitch::Init()
{
	if (!GetWorld()->GetFirstPlayerController())
		return;
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Posses", IE_Pressed, this, &ASwitch::Posses);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("UnPosses", IE_Pressed, this, &ASwitch::UnPosses);

}
