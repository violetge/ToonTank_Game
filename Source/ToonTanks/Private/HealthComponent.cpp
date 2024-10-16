// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;

	//绑定伤害事件
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	//获取GameMode
	ToonTankModeBase = Cast<AToonTankModeBase>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	if (Health <= 0 )
	{
		ToonTankModeBase->ActorDied(DamagedActor);
		//打印Health
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	}
}



