// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GrabBall.h"
#include "Ball.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GrabBall::UBTTask_GrabBall()
{
	NodeName = "Grab Ball";
}

EBTNodeResult::Type UBTTask_GrabBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }
   
    if (ABall* Ball = Cast<ABall>(BlackboardComp->GetValueAsObject("Ball")))
    {
        Ball->AttachToActor(OwnerComp.GetAIOwner()->GetPawn(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

        BlackboardComp->SetValueAsBool(GetSelectedBlackboardKey(), true);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

