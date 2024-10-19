// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankModeBase.h"
#include "Tank.h"
#include "EnemyTurrets.h"
#include "EnemyTank.h"
#include <Kismet/GameplayStatics.h>



AToonTankModeBase::AToonTankModeBase()
{
	StartDelay = 3.0f; // 3�����������
	TargetTurrets = 0; // Ŀ����������
	TargetEnemyTanks = 0; // Ŀ��з�̹������
}

void AToonTankModeBase::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart(); //��ʼ��Ŀ����������
	GetTargetEnemyTankCount(); //��ʼ��Ŀ��з�̹�˼���

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

	UE_LOG(LogTemp, Warning, TEXT("TargetEnemyTanks: %d"), TargetEnemyTanks);


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
	TArray<AActor*> EnemyTankActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTank::StaticClass(), EnemyTankActors);
	return EnemyTankActors.Num();
}
