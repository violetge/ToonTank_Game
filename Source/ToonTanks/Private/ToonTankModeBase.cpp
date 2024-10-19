// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankModeBase.h"
#include "Tank.h"
#include "EnemyTurrets.h"
#include "EnemyTank.h"
#include <Kismet/GameplayStatics.h>



AToonTankModeBase::AToonTankModeBase()
{
	StartDelay = 3.0f; // 3秒后启用输入
	TargetTurrets = 0; // 目标炮塔数量
	TargetEnemyTanks = 0; // 目标敌方坦克数量
}

void AToonTankModeBase::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart(); //初始化目标炮塔计数
	GetTargetEnemyTankCount(); //初始化目标敌方坦克计数

	// 设置定时器 3秒后启用输入
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
	OnGameOver(false); //游戏结束 显示UI
	UE_LOG(LogTemp, Warning, TEXT("OnGameOver(false); //游戏结束"));
	Tank->HandleDestruction();

	if (ToonTankPlayerController)
	{
		//设置玩家控制器不可输入  下面俩条语句等价  ture表示死亡
		ToonTankPlayerController->SetTankPlayerControl(true);
		/*ToonTankPlayerController->GetPawn()->DisableInput(ToonTankPlayerController);*/

		//显示鼠标光标
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
		OnGameOver(true); //游戏胜利 显示UI
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
