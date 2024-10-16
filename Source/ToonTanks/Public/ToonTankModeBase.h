// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <ToonTankPlayerController.h>
#include "ToonTankModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AToonTankModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartDelay")
	float StartDelay;
	
	void ActorDied(AActor* DeadActor);
	void EnableTankInput();


	// 游戏结束 显示UI BlueprintImplementableEvent 用于蓝图实现
	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
	void OnGameOver(bool bWon);

private:
	class ATank* Tank;
	class AEnemyTurrets* EnemyTurrets;
	AToonTankPlayerController* ToonTankPlayerController;

	// 定时器句柄
	FTimerHandle InputTimerHandle;

	void HandleGameStart();


	int32 TargetTurrets;
	int32 GetTargetTurretCount();
};
