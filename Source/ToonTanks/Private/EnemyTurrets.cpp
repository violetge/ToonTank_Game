// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurrets.h"
#include "TimerManager.h"

AEnemyTurrets::AEnemyTurrets()
{
	PrimaryActorTick.bCanEverTick = true;

	FireRate = 2.0f;
	FireRange = 500.0f;
}

void AEnemyTurrets::BeginPlay()
{
	// 查找场景中的坦克
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// 设置定时器
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTurrets::Fire, FireRate, true);

	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy")); // 添加标签

	// 设置为敌人控制
	bIsPlayerControlled = false;
}


void AEnemyTurrets::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	TankLocation = Tank->GetActorLocation();
	RotateTurret(TankLocation);

	// 检查坦克是否在射程内并控制定时器
	if (isFierRange())
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle))
		{
			// 如果定时器未激活，则启动定时器
			GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTurrets::Fire, FireRate, true);
		}
	}
	else
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle))
		{
			// 如果定时器已激活，则停止定时器
			GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
		}
	}
}

void AEnemyTurrets::RotateTurret(FVector TargetLocation)
{
	if (isFierRange())
	{

		FVector TurretLocation = Turret->GetComponentLocation();

		FVector ToTarget = TargetLocation - TurretLocation;

		FRotator TargetRotation = ToTarget.Rotation();

		Turret->SetWorldRotation(FRotator(0, TargetRotation.Yaw, 0));
	}
}

bool AEnemyTurrets::isFierRange()
{
	if (Tank)
	{
		//计算与tank的距离
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void AEnemyTurrets::HandleDestruction()
{
	Super::HandleDestruction();
	// 播放死亡动画
	// 播放声音
	// 隐藏模型

	// 生成粒子效果
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
	// 销毁Actor
	Destroy();
}




