// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExamProjectGameMode.h"
#include "ExamProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AExamProjectGameMode::AExamProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AExamProjectGameMode::ResetMatch()
{
	TargetPoints.Empty();
	GameBalls.Empty();

	for (TActorIterator<ATargetPoint> It(GetWorld()); It; ++It)
	{
		TargetPoints.Add(*It);
	}

	for (TActorIterator<ABall> It(GetWorld()); It; ++It)
	{
		if (It->GetAttachParentActor())
		{
			It->AttachToActor(nullptr, FAttachmentTransformRules::KeepWorldTransform);
		}

		GameBalls.Add(*It);
	}

	TArray<ATargetPoint*> RandomTargetPoints = TargetPoints;

	for (int32 i = 0; i < GameBalls.Num(); i++)
	{
		const int32 RandomTargetIndex = FMath::RandRange(0, RandomTargetPoints.Num() - 1);
		GameBalls[i]->SetActorLocation(RandomTargetPoints[RandomTargetIndex]->GetActorLocation());
		RandomTargetPoints.RemoveAt(RandomTargetIndex);
	}
}

const TArray<ABall*>& AExamProjectGameMode::GetBalls() const
{
	return GameBalls;
}

void AExamProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	ResetMatch();
}

void AExamProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//for (int32 i = 0; i < GameBalls.Num(); i++)
	//{
	//	if (GameBalls[i]->GetAttachParentActor() != GetWorld()->GetFirstPlayerController()->GetPawn())
	//	{
	//		return;
	//	}
	//}

	//ResetMatch();
}