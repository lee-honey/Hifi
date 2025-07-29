// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHalfBeatCircleWidget.h"
#include "Components/Image.h" 
#include "Beat/ABBeatManager.h"

UABHalfBeatCircleWidget::UABHalfBeatCircleWidget(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer)
{
}

void UABHalfBeatCircleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetBeatTime(static_cast<float>(GetGameInstance()->GetSubsystem<UABBeatManager>()->GetBPM()));

	HalfBeatCircle_L = Cast<UImage>(GetWidgetFromName(TEXT("HalfBeatCircle_L")));
	ensure(HalfBeatCircle_L);

	HalfBeatCircle_R = Cast<UImage>(GetWidgetFromName(TEXT("HalfBeatCircle_R")));
	ensure(HalfBeatCircle_R);

	SetCircleVisible(false);
}

void UABHalfBeatCircleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HalfBeatCircle_L->IsVisible() || !HalfBeatCircle_R->IsVisible())
		return;

	if (IsValid(HalfBeatCircle_L) && IsValid(HalfBeatCircle_R))
	{
		MoveTimer += InDeltaTime * 0.25f;

		Translate(HalfBeatCircle_L, FVector2D(-450.f, 0.f), FVector2D(-23.f, 0.f), InDeltaTime);
		Translate(HalfBeatCircle_R, FVector2D(450.f, 0.f), FVector2D(23.f, 0.f), InDeltaTime);
	}
}

void UABHalfBeatCircleWidget::Translate(UWidget* Widget, const FVector2D& StartPos, const FVector2D& TargetPos, float InDeltaTime)
{
	if (!Widget) return;

	float Progress = FMath::Clamp(MoveTimer / BeatTime, 0.f, 1.f);

	if (Progress < 1.f)
	{
		FVector2D NewPos = FMath::Lerp(StartPos, TargetPos, Progress);

		FWidgetTransform Transform = Widget->RenderTransform;
		Transform.Translation = NewPos;
		Widget->SetRenderTransform(Transform);
		Widget->SetRenderOpacity(Progress); // 투명도조절
	}
	else
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
		MoveTimer = 0.f;
	}
}

void UABHalfBeatCircleWidget::SetCircleVisible(bool bIsVisible)
{
	if (bIsVisible)
	{
		HalfBeatCircle_L->SetVisibility(ESlateVisibility::Visible);
		HalfBeatCircle_R->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HalfBeatCircle_L->SetVisibility(ESlateVisibility::Hidden);
		HalfBeatCircle_R->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UABHalfBeatCircleWidget::GetCircleVisible()
{
	return HalfBeatCircle_L->IsVisible();
}
