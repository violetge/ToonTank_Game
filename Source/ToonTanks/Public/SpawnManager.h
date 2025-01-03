// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class TOONTANKS_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void SpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // 预定义的敌人坦克刷新点
    UPROPERTY(EditAnywhere)
    TArray<FVector> SpawnPoints;

    // 敌人坦克类
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AEnemyTank> EnemyTankClass;

    // 刷新间隔
    UPROPERTY(EditAnywhere)
    float SpawnInterval;

    // 最大生成敌人数量
    UPROPERTY(EditAnywhere)
    int32 MaxSpawnCount;

    // 已生成敌人数量
    int32 SpawnedEnemyCount;

    // 定时器句柄
    FTimerHandle SpawnTimerHandle;

};
