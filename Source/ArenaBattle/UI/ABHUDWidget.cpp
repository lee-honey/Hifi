// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHUDWidget.h"
#include "Beat/ABBeatManager.h"

UABHUDWidget::UABHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HalfBeatCircle = Cast<UABHalfBeatCircleWidget>(GetWidgetFromName(TEXT("WBP_HalfBeatCircle")));
	ensure(HalfBeatCircle);

	SetBeatTime(static_cast<float>(GetGameInstance()->GetSubsystem<UABBeatManager>()->GetBPM()));

	for (int i = 0; i < 8; ++i)
	{
		UClass* HalfBeatClass = HalfBeatCircle->GetClass();
		UABHalfBeatCircleWidget* Widget = CreateWidget<UABHalfBeatCircleWidget>(GetWorld(), HalfBeatClass);
		Widget->AddToViewport(999);
		Widget->SetCircleVisible(false);

		FWidgetTransform Transform;
		Transform.Translation = FVector2D(0.f, 390.f);
		Widget->SetRenderTransform(Transform);
		
		HalfBeatWidgetPool.Add(Widget);
	}
}

UABHalfBeatCircleWidget* UABHUDWidget::GetAvailableWidget()
{
	for (UABHalfBeatCircleWidget* Widget : HalfBeatWidgetPool)
	{
		if (Widget->GetCircleVisible() == false)
		{
			return Widget;
		}
	}
	return nullptr;
}

void UABHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SpawnTimer += InDeltaTime;

	if (SpawnTimer >= BeatTime)
	{
		if (UABHalfBeatCircleWidget* Widget = GetAvailableWidget())
		{
			Widget->SetCircleVisible(true);
		}

		SpawnTimer = 0.f;
	}
}
