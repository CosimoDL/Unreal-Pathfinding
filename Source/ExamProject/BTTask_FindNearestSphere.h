// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindNearestSphere.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPROJECT_API UBTTask_FindNearestSphere : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_FindNearestSphere();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	static TArray<ABall*> SelectedBalls;

private:
	ABall* FindNearestBall(UBehaviorTreeComponent& OwnerComp);
};
