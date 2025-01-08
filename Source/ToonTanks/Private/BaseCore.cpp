// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCore.h"

// Sets default values
ABaseCore::ABaseCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseCoreMesh"));
	RootComponent = BaseCoreMesh;

}

// Called when the game starts or when spawned
void ABaseCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCore::HandleDestruction()
{
	Destroy(); //Ïú»Ù×Ô¼º
}

