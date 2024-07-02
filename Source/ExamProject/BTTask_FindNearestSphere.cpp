// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNearestSphere.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "ExamProjectGameMode.h"

TArray<ABall*> UBTTask_FindNearestSphere::SelectedBalls;

UBTTask_FindNearestSphere::UBTTask_FindNearestSphere()
{
    NodeName = "Find Nearest Sphere";
}

EBTNodeResult::Type UBTTask_FindNearestSphere::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ABall* NearestSphere = FindNearestBall(OwnerComp);

    if (NearestSphere)
    {
        SelectedBalls.Add(NearestSphere);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NearestSphere->GetActorLocation());
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

ABall* UBTTask_FindNearestSphere::FindNearestBall(UBehaviorTreeComponent& OwnerComp)
{
    ANPCAIController* AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        return nullptr;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return nullptr;
    }

    FVector AILocation = AIPawn->GetActorLocation();
    AGameModeBase* GameMode = AIController->GetWorld()->GetAuthGameMode();
    AExamProjectGameMode* AIGameMode = Cast<AExamProjectGameMode>(GameMode);
    const TArray<ABall*>& BallsList = AIGameMode->GetBalls();

    ABall* NearestSphere = nullptr;
    float MinDistance = FLT_MAX;

    for (ABall* Ball : BallsList)
    {
        if (!Ball->GetAttachParentActor() && !SelectedBalls.Contains(Ball))
        {
            float Distance = FVector::Dist(AILocation, Ball->GetActorLocation());

            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                NearestSphere = Ball;
            }
        }
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsObject("Ball", NearestSphere);
    return NearestSphere;
}
