// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 100;
	RotationSpeed = 45;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArm);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

	PlayerControllerRef->SetShowMouseCursor(true);

}

void ATank::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);

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

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}




void ATank::RotateTurret(FVector TargetLocation)
{
	// 获取炮塔的当前位置
	FVector TurretLocation = Turret->GetComponentLocation();

	FVector ToTarget = TargetLocation - TurretLocation;

	FRotator TargetRotation = ToTarget.Rotation();

	Turret->SetWorldRotation(FRotator(0, TargetRotation.Yaw, 0));


}
