// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABHalfBeatCircleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHalfBeatCircleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UABHalfBeatCircleWidget(const FObjectInitializer& ObjectInitializer);

public:
	void SetCircleVisible(bool bIsVisible);
	bool GetCircleVisible();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	void SetBeatTime(const float InBPM) { BeatTime = (1.f / (InBPM / 60.f)); }
	void Translate(UWidget* Widget, const FVector2D& StartPos, const FVector2D& TargetPos, float InDeltaTime);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> HalfBeatCircle_L;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> HalfBeatCircle_R;

	float MoveTimer;
	float BeatTime;
	float lX;
	float rX;
};
