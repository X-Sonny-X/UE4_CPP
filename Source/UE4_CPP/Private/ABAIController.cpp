// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));

AABAIController::AABAIController()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/InfinityBladeGrassLands/AI/BB_ABCharacter.BB_ABCharacter"));
    if(BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/InfinityBladeGrassLands/AI/BT_ABCharacter.BT_ABCharacter"));
    if(BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }
}

void AABAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if(UseBlackboard(BBAsset, Blackboard))
    {
        Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
        if(!RunBehaviorTree(BTAsset))
        {
            ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
        }
    }
}