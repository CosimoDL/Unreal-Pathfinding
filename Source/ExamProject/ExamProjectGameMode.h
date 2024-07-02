// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineUtils.h"
#include "Ball.h"
#include "Engine/TargetPoint.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExamProjectGameMode.generated.h"

UCLASS(minimalapi)
class AExamProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	TArray<ATargetPoint*> TargetPoints;
	TArray<ABall*> GameBalls;

public:
	AExamProjectGameMode();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void ResetMatch();
	const TArray<ABall*>& GetBalls() const;
};



