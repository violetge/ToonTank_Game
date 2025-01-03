// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "SpawnPoint.h" // 确保包含了 SpawnPoint 的头文件
#include "EnemyTank.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnInterval = 5.0f;
	MaxSpawnCount = 10;
	SpawnedEnemyCount = 0;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// 获取所有的 SpawnPoint 实例
	TArray<AActor*> FoundSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), FoundSpawnPoints);

	// 初始化 SpawnPoints 数组
	for (AActor* Actor : FoundSpawnPoints)
	{
		ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(Actor);
		if (SpawnPoint)
		{
			SpawnPoints.Add(SpawnPoint->GetActorLocation());
		}
	}

	// 启动定时器，每隔 SpawnInterval 秒调用一次 SpawnEnemy 函数
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnManager::SpawnEnemy, SpawnInterval, true);
	
}


void ASpawnManager::SpawnEnemy()
{
	if (SpawnedEnemyCount >= MaxSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		UE_LOG(LogTemp, Display, TEXT("SpawnedEnemyCount >= MaxSpawnCount"));
		return;
	}
	//选择一个随机的地方刷新
	if (SpawnPoints.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("SpawnPointIndex"));
		int32 SpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FVector SpawnLocation = SpawnPoints[SpawnPointIndex];

		GetWorld()->SpawnActor<AEnemyTank>(EnemyTankClass, SpawnLocation, FRotator::ZeroRotator);

		SpawnedEnemyCount++;
		//打印SpawnedEnemyCount
		UE_LOG(LogTemp, Display, TEXT("SpawnedEnemyCount : %d"), SpawnedEnemyCount);

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("NO SpawnPointIndex"));
	}
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

