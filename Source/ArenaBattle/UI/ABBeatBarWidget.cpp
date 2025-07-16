// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABBeatBarWidget.h"
#include "Components/Image.h" 
#include "Beat/ABBeatManager.h"

UABBeatBarWidget::UABBeatBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UABBeatBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIBeatCat = Cast<UImage>(GetWidgetFromName(TEXT("UIBeatCat")));
	ensure(UIBeatCat);

	SetBeatTime(static_cast<float>(GetGameInstance()->GetSubsystem<UABBeatManager>()->GetBPM()));
	SetScale(FVector2D(90.f, 90.f));
	InitScale = UIBeatCat->Brush.ImageSize;
}

void UABBeatBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsValid(UIBeatCat))
	{
		UIScalingToBeat(InDeltaTime);
	}
}

void UABBeatBarWidget::UIScalingToBeat(float InDeltaTime)
{
	ScaleTimer += InDeltaTime;

	if (ScaleTimer <= BeatTime)
	{
		float Progress = ScaleTimer / BeatTime;
		
		FVector2D CurImageSize = UIBeatCat->Brush.ImageSize;
		FVector2D NextImageSize = Progress * (InitScale - Scale) + Scale;

		FVector2D FinalImageSize = FMath::Lerp(CurImageSize, NextImageSize, 0.5f);

		UIBeatCat->Brush.SetImageSize(FinalImageSize);
	}
	else if (ScaleTimer > BeatTime)
	{
		ScaleTimer = 0.f;
	}
}
