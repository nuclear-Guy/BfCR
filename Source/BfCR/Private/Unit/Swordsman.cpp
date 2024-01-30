// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/Swordsman.h"
#include "UObject/ConstructorHelpers.h"


ASwordsman::ASwordsman() {

	UStaticMeshComponent* SwordsmanBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SwordsmanBody->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SwordsmanAsset(TEXT("/Script/Engine.StaticMesh'/Game/Characters/Meshes/Swordsman/StaticMesh.StaticMesh'"));

	if (SwordsmanAsset.Succeeded())
	{
		SwordsmanBody->SetStaticMesh(SwordsmanAsset.Object);
		SwordsmanBody->SetRelativeLocation(FVector(0.0f, 0.0f, -GetDefaultHalfHeight()));
		SwordsmanBody->SetWorldScale3D(FVector(1.f));
		SwordsmanBody->AddRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

}


void ASwordsman::BeginPlay() {
	Super::BeginPlay();
}
