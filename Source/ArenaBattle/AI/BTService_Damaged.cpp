// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Damaged.h"
#include "ABAI.h"
#include "AIController.h"
#include "Animation/ABAnimInstance.h"
#include "Character/ABCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Damaged::UBTService_Damaged()
{
	NodeName = TEXT("Damaged");
	Interval = 0.2f;
}

void UBTService_Damaged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;

	UABAnimInstance* AnimInstance = Cast<UABAnimInstance>(Cast<AABCharacterBase>(ControllingPawn)->GetMesh()->GetAnimInstance());

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISHIT, AnimInstance->GetIsHit());
}
