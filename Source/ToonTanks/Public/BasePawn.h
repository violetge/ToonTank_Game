// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HealthComponent.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Turret;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UFloatingPawnMovement* MovementComponent;  // 添加移动组件


	UPROPERTY(EditAnywhere, Category = "Projectile Type")
	TSubclassOf<class AProjectile> ProjectileClass;

	void HandleDestruction();
	void Fire();
protected:
	// 标识坦克是否由玩家控制
	bool bIsPlayerControlled;

private:



};
