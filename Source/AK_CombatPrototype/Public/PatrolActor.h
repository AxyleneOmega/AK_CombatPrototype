// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_PatrolRoute.h"
#include "Components/SplineComponent.h"
#include "PatrolActor.generated.h"

//Patrol Actor with spline component and functions to fetch indices, locations along spline points

UCLASS(Blueprintable)
class AK_COMBATPROTOTYPE_API APatrolActor : public AActor, public IBPI_PatrolRoute
{
    GENERATED_BODY()

public:
    APatrolActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol")
    USplineComponent* SplineComponent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Patrol")
    int32 CurrentIndex;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Patrol")
    int32 Direction;

    UFUNCTION(BlueprintCallable, Category = "Patrol")
    void SplineIndexIncrement(int32& OutIndex, int32& OutDirection);

    //BPI_PatrolRoute Interface Implementations
    virtual void GetSplinePointAsWorldPositionWithIncrement_Implementation(FVector& PointLocation, int32& NextPointIndex) override;

    virtual void GetNearestSplinePointLocation_Implementation(const FVector& LocationToCheck, const AActor* TargetToCheck, int32& NearestPointIndex, FVector& NearestPointLocation, float& DistanceToNearest) override;
};

