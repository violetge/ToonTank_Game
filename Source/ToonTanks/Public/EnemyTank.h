// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTank : public ATank
{
	GENERATED_BODY()
	
public:
	AEnemyTank();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 处理敌人死亡的逻辑
	void HandleDestruction();
	
private:
	class AEnemyTankController* EnemyTankController;

	FVector MoveDirectionDelta;
	FVector PreviousLocation;

};
