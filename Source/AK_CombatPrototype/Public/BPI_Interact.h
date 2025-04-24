// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Interact.generated.h"

// BPI_Interact - Blueprintable interface for interaction (with Weapon Actors, etc)

UINTERFACE(BlueprintType)
class AK_COMBATPROTOTYPE_API UBPI_Interact : public UInterface
{
	GENERATED_BODY()
};

class AK_COMBATPROTOTYPE_API IBPI_Interact
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	AActor* RegisterInteractable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	bool OnInteract(AActor* InteractingActor);
};
