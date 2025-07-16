h// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABBeatHalfCircleWidget.h"
#include "Beat/ABBeatManager.h"

UABBeatHalfCircleWidget::UABBeatHalfCircleWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UABBeatHalfCircleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UABBeatHalfCircleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
