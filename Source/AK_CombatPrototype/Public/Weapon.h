// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWeaponData.h"
#include "BPI_Interact.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable)
class AK_COMBATPROTOTYPE_API AWeapon : public AActor, public IBPI_Interact
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY()
	bool bIsEquipped = false;

	void UpdateWeaponPhysics();

public:
	//PROPERTIES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ExposeOnSpawn = true))
	FWeaponData WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ExposeOnSpawn = true))
	float PickupRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ExposeOnSpawn = true))
	FTransform EquippedRelativeTransform = FTransform::Identity;

	//FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FName GetWeaponName() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FName GetAttachSocketName() const;

	// Interface
	virtual AActor* RegisterInteractable_Implementation() override;
	virtual bool OnInteract_Implementation(AActor* InteractingActor) override;
};
