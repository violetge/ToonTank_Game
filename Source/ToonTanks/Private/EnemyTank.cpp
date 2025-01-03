// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "EnemyTankController.h"
#include <Kismet/GameplayStatics.h>

AEnemyTank::AEnemyTank()
{
	PrimaryActorTick.bCanEverTick = true;
	if (CameraComponent)
	{
		CameraComponent->DestroyComponent();
	}
	SpringArm->DestroyComponent();

	
	Tags.Add(FName("Enemy")); // ��ӱ�ǩ

	// ����Ϊ���˿��Ƶ�̹��
	bIsPlayerControlled = false;


}

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();

	EnemyTankController = Cast<AEnemyTankController>(GetController());  // ��ȡ������
	// ��ʼ����һ֡��λ��
	PreviousLocation = GetActorLocation();

}

void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���㵱ǰ֡��λ��
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += MoveDirectionDelta * DeltaTime * 100.0f;
	SetActorLocation(CurrentLocation);


	// �����ƶ�����
	FVector MoveDirection = CurrentLocation - PreviousLocation;


	// ����ƶ�����Ϊ�㣬����̹�˵���ת
	if (!MoveDirection.IsNearlyZero())
	{
		FRotator TargetRotation = MoveDirection.Rotation();
		Base->SetWorldRotation(TargetRotation);
	}

	// ������һ֡��λ��
	PreviousLocation = CurrentLocation;
}

void AEnemyTank::HandleDestruction()
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



