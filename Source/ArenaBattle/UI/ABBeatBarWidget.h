// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/ABBeatUIScaleInterface.h"
#include "ABBeatBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABBeatBarWidget : public UUserWidget, public IABBeatUIScaleInterface
{
	GENERATED_BODY()

public:
	UABBeatBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	// ui move interface
	virtual void UIScalingToBeat(float InDeltaTime) override;
	void SetBeatTime(const float InBPM){BeatTime = (1.f / (InBPM / 60.f));}
	void SetScale(const FVector2D InScale) { Scale = InScale; }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> UIBeatCat;

};
