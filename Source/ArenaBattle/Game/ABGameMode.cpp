// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "ABGameMode.h"
#include "Beat/ABBeatManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ABBeatBarWidget.h"

AABGameMode::AABGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

}

void AABGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (BackGroundMusic)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BackGroundMusic);

		if (GetGameInstance()->GetSubsystem<UABBeatManager>())
		{
			GetGameInstance()->GetSubsystem<UABBeatManager>()->SetBeatInitialize(140);
		}
	}

	if (BeatUIClass)
	{
		BeatUIInstance = CreateWidget<UABBeatBarWidget>(GetWorld(), BeatUIClass);
		if (BeatUIInstance.IsNull() == false)
		{
			BeatUIInstance->AddToViewport();
		}
	}
}
