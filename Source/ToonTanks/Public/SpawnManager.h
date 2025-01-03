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

    // Ԥ����ĵ���̹��ˢ�µ�
    UPROPERTY(EditAnywhere)
    TArray<FVector> SpawnPoints;

    // ����̹����
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AEnemyTank> EnemyTankClass;

    // ˢ�¼��
    UPROPERTY(EditAnywhere)
    float SpawnInterval;

    // ������ɵ�������
    UPROPERTY(EditAnywhere)
    int32 MaxSpawnCount;

    // �����ɵ�������
    int32 SpawnedEnemyCount;

    // ��ʱ�����
    FTimerHandle SpawnTimerHandle;

};
