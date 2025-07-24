// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABCharacterStat.h"
#include "ABGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogABGameSingleton, Error, All);
/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UABGameSingleton();
	static UABGameSingleton& Get();


	// Character Stat Data Section
public: // 외부에서 가져올 수 있도록 하는 함수. 유효하다면 바로 가져오고 아닐경우 기본생성자 가져와 넘겨주도록
	FORCEINLINE FABCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FABCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel; // 총몇개레벨이있는지에대한정보는 public으로 바로 가져올수있도록

private:
	TArray<FABCharacterStat> CharacterStatTable;
};
