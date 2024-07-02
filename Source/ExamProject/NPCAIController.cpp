// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCAIController.h"
#include "NPC.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ExamProjectGameMode.h"
#include "ExamProjectCharacter.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const Npc = Cast<ANPC>(InPawn))
	{
		if (UBehaviorTree* const BehaviorTree = Npc->GetBehaviorTree())
		{
			UBlackboardComponent* BlackboardComponent;
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
			Blackboard = BlackboardComponent;
			RunBehaviorTree(BehaviorTree);
		}
	}
}

void ANPCAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense((*SightConfig));
	}
}

void ANPCAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const Charac = Cast<AExamProjectCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
