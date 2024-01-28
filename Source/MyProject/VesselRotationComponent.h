// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VesselRotationComponent.generated.h"


class AVessel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UVesselRotationComponent : public UActorComponent
{
	GENERATED_BODY()

	/** AVessel that owns this component. */
	UPROPERTY(Transient, DuplicateTransient)
	mutable TObjectPtr<class AVessel> VesselOwner;
public:
	// Sets default values for this component's properties
	UVesselRotationComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Vessel|Components|VesselRotation")
	class AVessel* GetVesselOwner() const;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Vessel|VesselRotation|Components|Input", meta = (Keywords = "AddInput"))
	virtual void AddYawInput(double Yaw, bool bForce = false);
	UFUNCTION(BlueprintCallable, Category = "Vessel|VesselRotation|Components|Input", meta = (Keywords = "AddInput"))
	virtual void AddPitchInput(double Pitch, bool bForce = false);
	UFUNCTION(BlueprintCallable, Category = "Vessel|VesselRotation|Components|Input", meta = (Keywords = "AddInput"))
	virtual void AddRollInput(double Roll, bool bForce = false);


	UFUNCTION(BlueprintCallable, Category = "Vessel|Components|VesselRotation")
	virtual void AddRotation(const FQuat& Quat, bool bForce = false) {};

};
