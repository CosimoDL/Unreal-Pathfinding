// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"	


UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, PlayerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
