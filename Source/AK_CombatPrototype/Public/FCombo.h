// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FAction.h"
#include "FCombo.generated.h"

//FCombo Data Struct - Each combo holds an array of actions mapped to ComboName
USTRUCT(BlueprintType)
struct FCombo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
    FName ComboName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
    TArray<FAction> Actions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo", meta = (MultiLine = true))
    FText Description;

    FCombo()
        : ComboName(NAME_None)
    {}
};
