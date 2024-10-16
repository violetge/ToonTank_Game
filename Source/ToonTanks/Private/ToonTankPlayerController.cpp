// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"

AToonTankPlayerController::AToonTankPlayerController()
{
	
	
}


void AToonTankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	GetPawn()->DisableInput(this);


}

void AToonTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AToonTankPlayerController::SetTankPlayerControl(bool IsDead)
{
	if (IsDead)
	{
		GetPawn()->DisableInput(this);
	}
	else
	{
		GetPawn()->EnableInput(this);
	}
}


