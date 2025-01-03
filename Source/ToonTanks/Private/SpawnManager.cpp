// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "SpawnPoint.h" // ȷ�������� SpawnPoint ��ͷ�ļ�
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

	// ��ȡ���е� SpawnPoint ʵ��
	TArray<AActor*> FoundSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), FoundSpawnPoints);

	// ��ʼ�� SpawnPoints ����
	for (AActor* Actor : FoundSpawnPoints)
	{
		ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(Actor);
		if (SpawnPoint)
		{
			SpawnPoints.Add(SpawnPoint->GetActorLocation());
		}
	}

	// ������ʱ����ÿ�� SpawnInterval �����һ�� SpawnEnemy ����
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
	//ѡ��һ������ĵط�ˢ��
	if (SpawnPoints.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("SpawnPointIndex"));
		int32 SpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FVector SpawnLocation = SpawnPoints[SpawnPointIndex];

		GetWorld()->SpawnActor<AEnemyTank>(EnemyTankClass, SpawnLocation, FRotator::ZeroRotator);

		SpawnedEnemyCount++;
		//��ӡSpawnedEnemyCount
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

