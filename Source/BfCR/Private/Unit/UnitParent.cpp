// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitParent.h"

// Sets default values
AUnitParent::AUnitParent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitParent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

