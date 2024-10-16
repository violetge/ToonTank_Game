// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"


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

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
		if (HitEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true);
			UE_LOG(LogTemp, Warning, TEXT("SpawnEmitterAtLocation"));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());

	}







	//销毁炮弹
	Destroy();

}


