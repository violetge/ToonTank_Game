// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>
#include "EnemyTurrets.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTurrets : public ABasePawn
{
	GENERATED_BODY()
	

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	AEnemyTurrets();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank* Tank;

	FVector TankLocation;


	void RotateTurret(FVector TargetLocation);
	bool isFierRange();
	void HandleDestruction();



	// ¶¨Ê±Æ÷¾ä±ú
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurretFireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRange;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DeathParticle;


};
