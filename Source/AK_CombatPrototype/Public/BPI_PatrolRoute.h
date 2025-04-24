// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_PatrolRoute.generated.h"

UINTERFACE(Blueprintable)
class AK_COMBATPROTOTYPE_API UBPI_PatrolRoute : public UInterface
{
    GENERATED_BODY()
};

class AK_COMBATPROTOTYPE_API IBPI_PatrolRoute
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Patrol")
    void GetSplinePointAsWorldPositionWithIncrement(FVector& PointLocation, int32& NextPointIndex);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Patrol")
    void GetNearestSplinePointLocation(const FVector& LocationToCheck, const AActor* TargetToCheck, int32& NearestPointIndex, FVector& NearestPointLocation, float& DistanceToNearest);
};
