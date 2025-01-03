// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "EnemyTankController.h"
#include <Kismet/GameplayStatics.h>

AEnemyTank::AEnemyTank()
{
	PrimaryActorTick.bCanEverTick = true;
	if (CameraComponent)
	{
		CameraComponent->DestroyComponent();
	}
	SpringArm->DestroyComponent();

	
	Tags.Add(FName("Enemy")); // 添加标签

	// 设置为敌人控制的坦克
	bIsPlayerControlled = false;


}

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();

	EnemyTankController = Cast<AEnemyTankController>(GetController());  // 获取控制器
	// 初始化上一帧的位置
	PreviousLocation = GetActorLocation();

}

void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 计算当前帧的位置
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += MoveDirectionDelta * DeltaTime * 100.0f;
	SetActorLocation(CurrentLocation);


	// 计算移动方向
	FVector MoveDirection = CurrentLocation - PreviousLocation;


	// 如果移动方向不为零，更新坦克的旋转
	if (!MoveDirection.IsNearlyZero())
	{
		FRotator TargetRotation = MoveDirection.Rotation();
		Base->SetWorldRotation(TargetRotation);
	}

	// 更新上一帧的位置
	PreviousLocation = CurrentLocation;
}

void AEnemyTank::HandleDestruction()
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



