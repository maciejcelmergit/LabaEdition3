// Fill out your copyright notice in the Description page of Project Settings.


#include "HasLineOfSight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UHasLineOfSight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (UBlackboardComponent* BlackBoard = AIController->GetBlackboardComponent())
		{
			if (AActor* TargetActor = Cast<AActor>(BlackBoard->GetValueAsObject(TargetKey.SelectedKeyName))) 
			{
				return AIController->LineOfSightTo(TargetActor);
			}
		}
	}

	return false;
}
