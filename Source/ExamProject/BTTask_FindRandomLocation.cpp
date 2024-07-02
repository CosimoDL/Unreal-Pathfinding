// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NPCAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPCAIController* const AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const NPC = AIController->GetPawn())
		{
			FVector const Origin = NPC->GetActorLocation();
			if (auto* const NavySys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation NavLocation;
				if (NavySys->GetRandomPointInNavigableRadius(Origin, SearchRadius, NavLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
