// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitParent.h"

/**
 * 
 */
class BFCR_API Squad
{
public:
	Squad(TArray<AUnitParent*> &Actors);
	~Squad();

	void SelectSquad();
	void NotSelectSquad();

private:
	AUnitParent* Leader;
	TArray<AUnitParent*> Solders;
};
