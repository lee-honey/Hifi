// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABHalfBeatCircleWidget.h"
#include "ABHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UABHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UABHalfBeatCircleWidget* GetAvailableWidget();
	void SetBeatTime(const float InBPM) { BeatTime = (1.f / (InBPM / 60.f)); }

protected:
	UPROPERTY()
	TObjectPtr<class UABHalfBeatCircleWidget> HalfBeatCircle;

	TArray<UABHalfBeatCircleWidget*> HalfBeatWidgetPool;
	float SpawnTimer = 0.f;
	float BeatTime;
};
