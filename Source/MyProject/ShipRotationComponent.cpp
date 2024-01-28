// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipRotationComponent.h"
#include "Vessel.h"

inline UShipRotationComponent::UShipRotationComponent(const FObjectInitializer& ObjectInitializer)
	: UVesselRotationComponent(ObjectInitializer) {}

void UShipRotationComponent::AddRotation(const FQuat& Value, bool bForce) {
	Rotator *= Value;
	GetOwner()->GetRootComponent()->SetWorldRotation(FQuat(GetOwner()->GetRootComponent()->GetRelativeRotation()) * Value);
}

void UShipRotationComponent::AddTorque(const FVector& Value, bool bForce) {
	if (auto Primitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())) {
		if (GEngine) {
			const auto& msg = FString::Printf(TEXT("Add torq"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
		}
		Primitive->AddTorqueInDegrees(Value, NAME_None, true);
	}
}


void UShipRotationComponent::AddYawInput(double Yaw, bool bForce) {
	const auto& Prim = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if(Prim && AllowTorque) {
		AddTorque(Prim->GetForwardVector() * Yaw * 500, bForce);
	} else {
		AddRotation(FQuat::MakeFromEuler({ 0, 0, Yaw }), bForce);
	}
}

void UShipRotationComponent::AddPitchInput(double Pitch, bool bForce) {	
	const auto& Prim = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (Prim && AllowTorque) {
		AddTorque(Prim->GetRightVector() * Pitch * 500, bForce);
	} else {
		AddRotation(FQuat::MakeFromEuler({ 0, -Pitch, 0 }), bForce);
	}
}

void UShipRotationComponent::AddRollInput(double Roll, bool bForce) {
	const auto& Prim = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (Prim && AllowTorque) {
		AddTorque(Prim->GetForwardVector() * Roll * 500, bForce);
	} else {
		AddRotation(FQuat::MakeFromEuler({ Roll, 0, 0 }), bForce);
	}
}

void UShipRotationComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetOwner()) {		
		auto Primitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		if (Primitive && AllowTorque) { return; }
		//GetOwner()->GetRootComponent()->SetWorldRotation(Rotator * FQuat(GetOwner()->GetRootComponent()->GetRelativeRotation()));
	}
}
