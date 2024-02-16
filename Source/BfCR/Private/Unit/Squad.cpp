// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/Squad.h"

Squad::Squad(TArray<AUnitParent*> &Actors)
{
	for (AUnitParent*& Actor : Actors)
	{
		if (!Leader) {
			Leader = Actor;
		}
		else {
			Solders.Add(Actor);
		}
	}
}

Squad::~Squad()
{
}

void Squad::SelectSquad()
{
	for (AUnitParent*& Actor : Solders)
	{
		Actor->GetMesh()->SetRenderCustomDepth(true);
		Actor->GetMesh()->SetCustomDepthStencilValue(1);
	}

	Leader->GetMesh()->SetRenderCustomDepth(true);
	Leader->GetMesh()->SetCustomDepthStencilValue(1);
}

void Squad::NotSelectSquad()
{
	for (AUnitParent*& Actor : Solders)
	{
		Actor->GetMesh()->SetRenderCustomDepth(false);
	}

	Leader->GetMesh()->SetRenderCustomDepth(false);
}
