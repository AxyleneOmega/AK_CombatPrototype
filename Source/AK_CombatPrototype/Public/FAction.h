// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FAction.generated.h"

//FAction Struct - Each action holds data required to play animation montages 
USTRUCT(BlueprintType)
struct FAction : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    FName ActionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    UAnimMontage* AnimMontage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    float PlayRate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    float StartingPosition = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    FName StartingSection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    bool bStopAllMontages = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    float BaseDamage = 0.0f;

    FAction()
        : ActionName(NAME_None),
          AnimMontage(nullptr),
          PlayRate(1.0f),
          StartingPosition(0.0f),
          StartingSection(NAME_None),
          bStopAllMontages(true),
          BaseDamage(0.0f)
    {}
};
