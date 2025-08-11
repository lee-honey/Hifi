// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_NoHit.h"
#include "ABAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_NoHit::UBTTask_NoHit()
{
}

EBTNodeResult::Type UBTTask_NoHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISHIT, false);

	return EBTNodeResult::Succeeded;
}
