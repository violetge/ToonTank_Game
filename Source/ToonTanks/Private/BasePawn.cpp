// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h" // ȷ����ʹ�� AProjectile ֮ǰ��������ͷ�ļ�


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBase"));
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankTurret"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

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
	// ������������
	// ��������
	// ��������Ч��
	// ����ģ��
	// ����Actor
}

void ABasePawn::Fire()
{
	if (ProjectileClass)
	{
		// ��ȡ�ڵ����ɵ��λ�ú���ת
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		// �����ڵ�
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

		UE_LOG(LogTemp, Display, TEXT("fire"));

	}
}


