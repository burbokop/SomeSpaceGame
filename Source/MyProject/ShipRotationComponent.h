// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VesselRotationComponent.h"
#include "ShipRotationComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UShipRotationComponent : public UVesselRotationComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool AllowTorque = true;


	FQuat Rotator = FQuat::MakeFromEuler({ 0., 0., 0. });
public:
	UShipRotationComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Inherited via UVesselRotationComponent
	virtual void AddRotation(const FQuat& Value, bool bForce) override;
	void AddTorque(const FVector& Value, bool bForce);

	
	virtual void AddYawInput(double Yaw, bool bForce = false) override;
	virtual void AddPitchInput(double Pitch, bool bForce = false) override;
	virtual void AddRollInput(double Roll, bool bForce = false) override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
