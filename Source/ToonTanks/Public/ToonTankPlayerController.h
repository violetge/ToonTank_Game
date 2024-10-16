// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	AToonTankPlayerController();
	void SetTankPlayerControl(bool IsDead);
	
};
