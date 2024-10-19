// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTankController.h"
#include "EnemyTank.h"
#include <Kismet/GameplayStatics.h>
#include <NavigationSystem.h>
#include <GameFramework/Actor.h>



void AEnemyTankController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // 获取玩家控制的Pawn
	ControlledTank = Cast<AEnemyTank>(GetPawn()); // 获取控制的坦克

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemyTankController::FireAtPlayer, 3.0f, true);


    //GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemyTankController::MoveToRandomLocation, 3.0f, true);

	


}

void AEnemyTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

//void AEnemyTankController::MoveToRandomLocation()
//{
//    if (ControlledTank)
//    {
//        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
//        if (NavSystem)
//        {
//            FNavLocation RandomLocation;
//            if (NavSystem->GetRandomPointInNavigableRadius(ControlledTank->GetActorLocation(), 1000.0f, RandomLocation))
//            {
//                MoveToLocation(RandomLocation.Location);
//                UE_LOG(LogTemp, Warning, TEXT("Moving to random location: %s"), *RandomLocation.Location.ToString());
//            }
//        }
//    }
//
//    UE_LOG(LogTemp, Display, TEXT("MoveToRandomLocation()"));
//}



void AEnemyTankController::FireAtPlayer()
{
	// 调用父类的 Fire() 函数
	ControlledTank->Fire();
	UE_LOG(LogTemp, Warning, TEXT("Enemy Fire!"));
}