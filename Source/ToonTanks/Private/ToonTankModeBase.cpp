// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankModeBase.h"
#include "Tank.h"
#include "EnemyTurrets.h"
#include <Kismet/GameplayStatics.h>



AToonTankModeBase::AToonTankModeBase()
{
	StartDelay = 3.0f; // 3�����������
	TargetTurrets = 0; // Ŀ����������
}

void AToonTankModeBase::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart(); //��ʼ��Ŀ����������

	// ���ö�ʱ�� 3�����������
	GetWorld()->GetTimerManager().SetTimer(InputTimerHandle, this, &AToonTankModeBase::EnableTankInput, StartDelay, false);
	

}


void AToonTankModeBase::ActorDied(AActor* DeadActor)
{
	
	if (DeadActor == Tank)
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
	else if (DeadActor == (EnemyTurrets = Cast<AEnemyTurrets>(DeadActor)))
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
}

void AToonTankModeBase::EnableTankInput()
{
	ToonTankPlayerController->SetTankPlayerControl(false);
}





void AToonTankModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
}


int32 AToonTankModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTurrets::StaticClass(), TurretActors);
	return TurretActors.Num();
}
