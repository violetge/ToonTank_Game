// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankModeBase.h"
#include "Tank.h"
#include "EnemyTurrets.h"
#include "EnemyTank.h"
#include "SpawnManager.h"
#include "Wall.h"
#include <Kismet/GameplayStatics.h>



void AToonTankModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AToonTankModeBase::AToonTankModeBase()
{
	StartDelay = 3.0f; // 3�����������
	TargetTurrets = 0; // Ŀ����������
	TargetEnemyTanks = 0; // Ŀ��з�̹������
}

void AToonTankModeBase::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // ��ȡ��ҿ��Ƶ�Pawn
	SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(this, ASpawnManager::StaticClass())); // ��ȡ���ɹ�����
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart(); //��ʼ��

	// ���ö�ʱ�� 3�����������
	GetWorld()->GetTimerManager().SetTimer(InputTimerHandle, this, &AToonTankModeBase::EnableTankInput, StartDelay, false);
	

}


void AToonTankModeBase::ActorDied(AActor* DeadActor)
{
	
	if (DeadActor == Tank)
	{
		HandlePlayerTankDeath();
	}
	else if (DeadActor == (EnemyTurrets = Cast<AEnemyTurrets>(DeadActor)))
	{
		HandleEnemyTurretDeath(EnemyTurrets);
	}
	else if (DeadActor == (EnemyTank = Cast<AEnemyTank>(DeadActor)))
	{
		HandleEnemyTankDeath(EnemyTank);
	}
	else if (DeadActor == (Wall = Cast<AWall>(DeadActor)))
	{
		HandleWallDeath();

	}
}

void AToonTankModeBase::EnableTankInput()
{
	ToonTankPlayerController->SetTankPlayerControl(false);
}

void AToonTankModeBase::HandlePlayerTankDeath()
{
	OnGameOver(false); //��Ϸ���� ��ʾUI
	UE_LOG(LogTemp, Warning, TEXT("OnGameOver(false); //��Ϸ����"));
	Tank->HandleDestruction();

	if (ToonTankPlayerController)
	{
		//������ҿ�������������  �����������ȼ�  ture��ʾ����
		ToonTankPlayerController->SetTankPlayerControl(true);
		/*ToonTankPlayerController->GetPawn()->DisableInput(ToonTankPlayerController);*/

		//��ʾ�����
		ToonTankPlayerController->bShowMouseCursor = true;
	}
}

void AToonTankModeBase::HandleEnemyTurretDeath(AEnemyTurrets* DeadTurret)
{
	UE_LOG(LogTemp, Warning, TEXT("EnemyTurrets->HandleDestruction() called"));
	EnemyTurrets->HandleDestruction();

	TargetTurrets--;
	if (TargetTurrets == 0)
	{
		OnGameOver(true); //��Ϸʤ�� ��ʾUI
		ToonTankPlayerController->bShowMouseCursor = true;
	}
}

void AToonTankModeBase::HandleEnemyTankDeath(AEnemyTank* DeadTank)
{
	UE_LOG(LogTemp, Warning, TEXT("EnemyTank->HandleDestruction() called"));
	EnemyTank->HandleDestruction();
	TargetEnemyTanks--;
	if (TargetEnemyTanks == 0)
	{
		OnGameOver(true); //��Ϸʤ�� ��ʾUI
		ToonTankPlayerController->bShowMouseCursor = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("TargetEnemyTanks: %d"), TargetEnemyTanks);


}

void AToonTankModeBase::HandleWallDeath()
{
	Wall->HandleDestruction();

}





void AToonTankModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	TargetEnemyTanks = GetTargetEnemyTankCount();
}


int32 AToonTankModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTurrets::StaticClass(), TurretActors);
	return TurretActors.Num();
}

int32 AToonTankModeBase::GetTargetEnemyTankCount()
{
	return SpawnManager->MaxSpawnCount;
}
