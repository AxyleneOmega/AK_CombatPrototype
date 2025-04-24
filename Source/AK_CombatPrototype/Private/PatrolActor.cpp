// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolActor.h"

APatrolActor::APatrolActor()
{
    PrimaryActorTick.bCanEverTick = false;

    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    RootComponent = SplineComponent;
    CurrentIndex = 0;
    Direction = 1;
}

void APatrolActor::BeginPlay()
{
    Super::BeginPlay();
}

void APatrolActor::SplineIndexIncrement(int32& OutIndex, int32& OutDirection)
{
    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    CurrentIndex += Direction;

    if (CurrentIndex >= (NumPoints - 1))
    {
        Direction = -1;
    }
    else if (CurrentIndex <= 0)
    {
        Direction = 1;
    }

    OutIndex = CurrentIndex;
    OutDirection = Direction;
}

void APatrolActor::GetSplinePointAsWorldPositionWithIncrement_Implementation(FVector& PointLocation, int32& NextPointIndex)
{
    PointLocation = SplineComponent->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);
    int32 IncrementedPointDirection;
    SplineIndexIncrement(NextPointIndex, IncrementedPointDirection);
	//Here - the IncrementedPointDirection variaable is not used but required as container output in SplineIndexIncrement
}

void APatrolActor::GetNearestSplinePointLocation_Implementation(const FVector& LocationToCheck, const AActor* TargetToCheck, int32& NearestPointIndex, FVector& NearestPointLocation, float& DistanceToNearest)
{
    FVector CheckLoc;

    if (IsValid(TargetToCheck))
    {
        CheckLoc = TargetToCheck->GetActorLocation();
    }
    else
    {
        CheckLoc = LocationToCheck;
    }

    float MinDist = TNumericLimits<float>::Max();
    int32 MinPointIndex = 0;

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector PointLoc = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        float Dist = FVector::Dist(CheckLoc, PointLoc);

        if (Dist < MinDist)
        {
            MinDist = Dist;
            MinPointIndex = i;
        }
    }

    NearestPointIndex = MinPointIndex;
    NearestPointLocation = SplineComponent->GetLocationAtSplinePoint(MinPointIndex, ESplineCoordinateSpace::World);
    DistanceToNearest = MinDist;
}
