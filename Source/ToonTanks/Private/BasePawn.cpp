// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h" // 确保在使用 AProjectile 之前包含它的头文件
#include "Tank.h"



// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireRate = 2.0f;//2秒发射一次 蓝图可改
	bCanfire = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBase"));
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankTurret"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));  // 初始化移动组件

	RootComponent = CapsuleComponent;
	Base->SetupAttachment(CapsuleComponent);
	Turret->SetupAttachment(Base);
	ProjectileSpawnPoint->SetupAttachment(Turret);



	 


}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ABasePawn::HandleDestruction()
{
	// 播放死亡动画
	// 播放声音
	// 播放粒子效果
	// 隐藏模型
	// 销毁Actor
}

void ABasePawn::Fire()
{
	if (bCanfire && ProjectileClass)
	{
		// 获取炮弹生成点的位置和旋转
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		// 生成炮弹
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		if (Projectile)
		{
			// 检查是否为玩家控制的坦克发射
			bool bIsPlayerOwned = bIsPlayerControlled;
			Projectile->SetInstigatorTank(this); // 设置发射炮弹的坦克
			//打印bIsPlayerOwned
			UE_LOG(LogTemp, Display, TEXT("bIsPlayerOwned: %d"), bIsPlayerOwned);
			Projectile->SetOwnerType(bIsPlayerOwned);

			/*UE_LOG(LogTemp, Display, TEXT("fire"));*/
		}

		bCanfire = false;
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ABasePawn::ResetFire, FireRate, false);

	}
}

void ABasePawn::ResetFire()
{
	bCanfire = true;
}


