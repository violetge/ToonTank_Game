// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetOwnerType(bool bIsPlayerOwn);
	void SetInstigatorTank(AActor* InstigatorTank); // 添加函数声明

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// 粒子系统引用
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitEffect;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UParticleSystemComponent* Traill;

	AActor* InstigatorActor; // 添加指向发射坦克的指针

private:

	bool bIsPlayerOwned; // 标识子弹是否由玩家发射·
};
