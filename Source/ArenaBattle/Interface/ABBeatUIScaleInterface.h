// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABBeatUIScaleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UABBeatUIScaleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENABATTLE_API IABBeatUIScaleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UIScalingToBeat(float InDeltaTime) = 0;

protected:
	FVector2D Scale = FVector2D::ZeroVector;
	FVector2D InitScale = FVector2D::ZeroVector;
	float BeatTime = 0.f;
	float ScaleTimer = 0.f;
};
