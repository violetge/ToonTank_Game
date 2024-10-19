// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyTankController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTankController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	APawn* PlayerPawn;
	class AEnemyTank* ControlledTank;

	void MoveToRandomLocation();



	 //定时器句柄
	FTimerHandle FireTimerHandle;

	 //定时器回调函数
	void FireAtPlayer();
};
