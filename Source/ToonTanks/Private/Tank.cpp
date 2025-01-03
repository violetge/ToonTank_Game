// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 100;
	RotationSpeed = 45;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArm);

	Tags.Add(FName("PlayerTank")); // ��ӱ�ǩ

	
	// ����Ϊ��ҿ��Ƶ�̹��
	bIsPlayerControlled = true;

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	

}

void ATank::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult TraceHitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);

		DrawDebugSphere(GetWorld(), TraceHitResult.ImpactPoint, 20, 12, FColor::Red, false, -1.0f);

		RotateTurret(TraceHitResult.ImpactPoint);

	}


}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;

	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;

	AddActorLocalRotation(DeltaRotation, true);
}




void ATank::RotateTurret(FVector TargetLocation)
{
	// ��ȡ�����ĵ�ǰλ��
	FVector TurretLocation = Turret->GetComponentLocation();

	FVector ToTarget = TargetLocation - TurretLocation; 

	FRotator TargetRotation = ToTarget.Rotation();

	Turret->SetWorldRotation(FRotator(0, TargetRotation.Yaw, 0));


}

void ATank::HandleDestruction()
{
	// ������������
	// ��������
	// ��������Ч��
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
	// ����ģ��
	SetActorHiddenInGame(true);

	//����tick������
	SetActorTickEnabled(false);



}



APlayerController* ATank::GetPlayerController()
{
	return TankPlayerController;
}
