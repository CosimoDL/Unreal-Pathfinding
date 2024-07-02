// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GrabBall.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPROJECT_API UBTTask_GrabBall : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_GrabBall();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
