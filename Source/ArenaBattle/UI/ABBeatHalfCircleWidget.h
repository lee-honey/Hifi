// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/ABBeatUIScaleInterface.h"
#include "ABBeatHalfCircleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABBeatHalfCircleWidget : public UUserWidget , public IABBeatUIScaleInterface
{
	GENERATED_BODY()
	
public:
	UABBeatHalfCircleWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
