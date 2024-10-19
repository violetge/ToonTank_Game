// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurrets.h"
#include "TimerManager.h"

AEnemyTurrets::AEnemyTurrets()
{
	PrimaryActorTick.bCanEverTick = true;

	FireRate = 2.0f;
	FireRange = 500.0f;
}

void AEnemyTurrets::BeginPlay()
{
	// ���ҳ����е�̹��
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// ���ö�ʱ��
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTurrets::Fire, FireRate, true);

	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Enemy")); // ��ӱ�ǩ

	// ����Ϊ���˿���
	bIsPlayerControlled = false;
}


void AEnemyTurrets::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	TankLocation = Tank->GetActorLocation();
	RotateTurret(TankLocation);

	// ���̹���Ƿ�������ڲ����ƶ�ʱ��
	if (isFierRange())
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle))
		{
			// �����ʱ��δ�����������ʱ��
			GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTurrets::Fire, FireRate, true);
		}
	}
	else
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle))
		{
			// �����ʱ���Ѽ����ֹͣ��ʱ��
			GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
		}
	}
}

void AEnemyTurrets::RotateTurret(FVector TargetLocation)
{
	if (isFierRange())
	{

		FVector TurretLocation = Turret->GetComponentLocation();

		FVector ToTarget = TargetLocation - TurretLocation;

		FRotator TargetRotation = ToTarget.Rotation();

		Turret->SetWorldRotation(FRotator(0, TargetRotation.Yaw, 0));
	}
}

bool AEnemyTurrets::isFierRange()
{
	if (Tank)
	{
		//������tank�ľ���
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void AEnemyTurrets::HandleDestruction()
{
	Super::HandleDestruction();
	// ������������
	// ��������
	// ����ģ��

	// ��������Ч��
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
	// ����Actor
	Destroy();
}




