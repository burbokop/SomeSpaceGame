// Fill out your copyright notice in the Description page of Project Settings.


#include "VesselPossessComponent.h"
#include "Vessel.h"

// Sets default values for this component's properties
UVesselPossessComponent::UVesselPossessComponent(const FObjectInitializer& ObjectInitializer) 
	: UActorComponent(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AVessel* UVesselPossessComponent::GetVesselOwner() const {
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


// Called when the game starts
void UVesselPossessComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVesselPossessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UVesselPossessComponent::GivePossessionTo(AController* Controller) {
	if (const auto& Owner = GetVesselOwner()) {
		if (const auto& CurrentPossession = Controller->GetPawn<AVessel>()) {
			CurrentPossession->SetGhostMode(true);
			PrevPossession = CurrentPossession;
			Controller->Possess(Owner);
			return true;
		}
		UE_LOG(LogTemp, Error, TEXT("UVesselPossessComponent::GivePossessionTo: missing CurrentPossession"));
	}
	UE_LOG(LogTemp, Error, TEXT("UVesselPossessComponent::GivePossessionTo: retfalse"));
	return false;
}

bool UVesselPossessComponent::ReturnPossession(const FTransform& UnloadingTransform, const FVector& UnloadingVelocity) {
	if (const auto& Owner = GetVesselOwner()) {
		if (PrevPossession) {
			if (auto Controller = Owner->GetController()) {
				PrevPossession->SetGhostMode(false);

				PrevPossession->SetActorTransform(UnloadingTransform);

				if (auto PrimitiveRootComponent = PrevPossession->GetPrimitiveRootComponent()) {
					PrimitiveRootComponent->SetPhysicsLinearVelocity(UnloadingVelocity);
				}

				Controller->Possess(PrevPossession);
			}
		}
	}
	return false;
}

