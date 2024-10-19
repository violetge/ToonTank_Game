// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Tank.h" // ������ҿ��Ƶ�̹������Ϊ ATank
#include "EnemyTank.h" // �������̹������Ϊ AEnemyTank
#include "EnemyTurrets.h" // ���������������Ϊ AEnemyTurrets


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


	bIsPlayerOwned = false; // Ĭ���ӵ���������ҷ���
	Damage = 50;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//����ײ�¼�
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
                    UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true); // ��������Ч��
                }
        }
        else
        {
            // ����ǵ��˷�����ڵ�������Ƿ�������̹��
            if (OtherActor->ActorHasTag(FName("PlayerTank")))
            {
                UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
                if (HitEffect)
                {
                    UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true); // ��������Ч��
                }
            }
        }
		
		
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());

	}

	//�����ڵ�
	Destroy();

}


