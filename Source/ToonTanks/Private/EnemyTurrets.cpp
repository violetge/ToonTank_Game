// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurrets.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>

void AEnemyTurrets::BeginPlay()
{
	// 查找场景中的坦克
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyTurrets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TankLocation = Tank->GetActorLocation();
	RotateTurret(TankLocation);

}

void AEnemyTurrets::RotateTurret(FVector TargetLocation)
{
	FVector TurretLocation = Turret->GetComponentLocation();

	FVector ToTarget = TargetLocation - TurretLocation;

	FRotator TargetRotation = ToTarget.Rotation();

	Turret->SetWorldRotation(FRotator(0, TargetRotation.Yaw, 0));
}
