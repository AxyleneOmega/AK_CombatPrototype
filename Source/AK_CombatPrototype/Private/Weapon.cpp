// Fill out your copyright notice in the Description page of Project Settings.

// Weapon actor class to physically embody a weapon in the world & can be picked up by player
#include "Weapon.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	//Scene root component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	// Skeletal Mesh 
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(SceneRoot);
	WeaponMesh->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Collision Sphere - for overlap only
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(WeaponMesh);
	CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CollisionSphere->SetSphereRadius(PickupRadius);
	// Apply mesh if set
	if (WeaponData.WeaponSKM)
	{
		WeaponMesh->SetSkeletalMesh(WeaponData.WeaponSKM);
	}
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Ensure we simulate physics if not equipped at start
	if (!bIsEquipped)
	{
		WeaponMesh->SetSimulatePhysics(true);
		WeaponMesh->SetEnableGravity(true);
	}
}

FName AWeapon::GetWeaponName() const
{
	return WeaponData.WeaponName;
}

FName AWeapon::GetAttachSocketName() const
{
	return WeaponData.AttachSocketName;
}

AActor* AWeapon::RegisterInteractable_Implementation()
{
	return this;
}

bool AWeapon::OnInteract_Implementation(AActor* InteractingActor)
{
	if (!InteractingActor) return false;

	if (!bIsEquipped)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying Equip - WeaponMesh Relative Transform: %s"), *WeaponMesh->GetRelativeTransform().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Trying Equip - Weapon Actor World Transform: %s"), *GetActorTransform().ToString());

		// Step 1: Mark equipped
		bIsEquipped = true;

		// Step 2: Disable physics before changing transform
		UpdateWeaponPhysics();

		// Step 3: Apply transform safely with teleport flag
		WeaponMesh->SetRelativeTransform(EquippedRelativeTransform, false, nullptr, ETeleportType::TeleportPhysics);

		return true;
	}
	else
	{
		AActor* OwningActor = GetAttachParentActor();
		if (InteractingActor == OwningActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Trying Unequip - WeaponMesh Relative Transform: %s"), *WeaponMesh->GetRelativeTransform().ToString());
			UE_LOG(LogTemp, Warning, TEXT("Trying Unequip - Weapon Actor World Transform: %s"), *GetActorTransform().ToString());

			// Step 1: Clear transform with teleport
			WeaponMesh->SetRelativeTransform(FTransform::Identity, false, nullptr, ETeleportType::TeleportPhysics);

			// Step 2: Now allow physics again
			bIsEquipped = false;
			UpdateWeaponPhysics();

			return true;
		}
	}

	return false;
}

void AWeapon::UpdateWeaponPhysics()
{
	WeaponMesh->SetSimulatePhysics(!bIsEquipped);
	WeaponMesh->SetEnableGravity(!bIsEquipped);

	// Optional: reset velocity if unequipping
	if (!bIsEquipped)
	{
		WeaponMesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
		WeaponMesh->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}
}
