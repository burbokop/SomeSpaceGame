// Fill out your copyright notice in the Description page of Project Settings.

#include "VesselRotationComponent.h"
#include "Vessel.h"

// Sets default values for this component's properties



// Sets default values for this component's properties

inline UVesselRotationComponent::UVesselRotationComponent(const FObjectInitializer& ObjectInitializer)
	: UActorComponent(ObjectInitializer) 
{
	

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UVesselRotationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


AVessel* UVesselRotationComponent::GetVesselOwner() const {
	if (GetOwner() != VesselOwner.Get()) {
		if (!ensureMsgf(Cast<AVessel>(GetOwner()), TEXT("%s must be owned by a Vessel. Not by %s"), *GetName(), *AActor::GetDebugName(GetOwner()))) {
			UE_LOG(LogInit, Error, TEXT("%s must be owned by a Vessel"), *GetName());
			VesselOwner = nullptr;
			return VesselOwner;
		}
		VesselOwner = CastChecked<AVessel>(GetOwner());
	}

	return VesselOwner.Get();
}

// Called every frame
void UVesselRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVesselRotationComponent::AddYawInput(double Yaw, bool bForce) {
	//VesselOwner->GetActorUpVector();
	AddRotation(FQuat::MakeFromEuler({ 0, 0, Yaw }), bForce);
}

void UVesselRotationComponent::AddPitchInput(double Pitch, bool bForce) {
	//VesselOwner->GetActorRightVector();
	AddRotation(FQuat::MakeFromEuler({ 0, -Pitch, 0 }), bForce);
}

void UVesselRotationComponent::AddRollInput(double Roll, bool bForce) {
	//VesselOwner->GetActorForwardVector()

	AddRotation(FQuat::MakeFromEuler({ Roll, 0, 0 }), bForce);
}

