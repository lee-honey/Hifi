// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Damaged.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTService_Damaged : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Damaged();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
