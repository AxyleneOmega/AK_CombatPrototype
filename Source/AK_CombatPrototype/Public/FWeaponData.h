// Fill out your copyright notice in the Description page of Project Settings.

// Weapon Data Struct - Encapsulates data about weapons
#pragma once

#include "CoreMinimal.h"
#include "FCombo.h"
#include "FWeaponData.generated.h"

USTRUCT(BlueprintType)
struct AK_COMBATPROTOTYPE_API FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data Structure")
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data Structure")
	FName AttachSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data Structure")
	USkeletalMesh* WeaponSKM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data Structure")
	FName ComboName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data Structure")
	FCombo ComboData;

	FWeaponData();
	~FWeaponData();
};
