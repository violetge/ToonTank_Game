// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Tank.h" // 假设玩家控制的坦克类名为 ATank
#include "EnemyTank.h" // 假设敌人坦克类名为 AEnemyTank
#include "EnemyTurrets.h" // 假设敌人炮塔类名为 AEnemyTurrets


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	Traill = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Traill"));

	RootComponent = ProjectileMesh;	
	Traill->SetupAttachment(RootComponent);


	bIsPlayerOwned = false; // 默认子弹不是由玩家发射
	Damage = 50;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//绑定碰撞事件
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetOwnerType(bool bIsPlayerOwn)
{
	this->bIsPlayerOwned = bIsPlayerOwn;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
        if (bIsPlayerOwned)
        {
                UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
                if (HitEffect)
                {
                    UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true); // 生成粒子效果
                }
        }
        else
        {
            // 如果是敌人发射的炮弹，检查是否击中玩家坦克
            if (OtherActor->ActorHasTag(FName("PlayerTank")))
            {
                UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
                if (HitEffect)
                {
                    UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true); // 生成粒子效果
                }
            }
        }
		
		
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());

	}

	//销毁炮弹
	Destroy();

}


