// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VesselRotationComponent.h"
#include "VesselPossessComponent.h"
#include "Vessel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API AVessel : public APawn
{
	GENERATED_BODY()

	

public:
	// Sets default values for this pawn's properties
	AVessel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/** Return our RootComponent as PrimitiveRootComponent, else error. */
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Return our RootComponent as PrimitiveRootComponent, else error"), Category = Vessel)
	UPrimitiveComponent* GetPrimitiveRootComponent() const;

	/** Return our VesselRotationComponent, if we have one. By default, returns the first VesselRotationComponent found. Native classes that create their own movement component should override this method for more efficiency. */
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Return our VesselRotationComponent, if we have one."), Category = Vessel)
	virtual UVesselRotationComponent* GetRotationComponent() const;

	/** Return our VesselPossessComponent, if we have one. By default, returns the first VesselPossessComponent found. Native classes that create their own movement component should override this method for more efficiency. */
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Return our VesselPossessComponent, if we have one."), Category = Vessel)
	virtual UVesselPossessComponent* GetPossessComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Vessel|Input", meta = (Keywords = "AddInput"))
	void AddYawInput(double Yaw, bool bForce = false);
	UFUNCTION(BlueprintCallable, Category = "Vessel|Input", meta = (Keywords = "AddInput"))
	void AddPitchInput(double Pitch, bool bForce = false);
	UFUNCTION(BlueprintCallable, Category = "Vessel|Input", meta = (Keywords = "AddInput"))
	void AddRollInput(double Roll, bool bForce = false);


	UFUNCTION(BlueprintCallable, Category = "Vessel|Possess")
	bool GivePossessionTo(AController* Ctrl);

	UFUNCTION(BlueprintCallable, Category = "Vessel|Possess")
	bool ReturnPossession(const FTransform& UnloadingTransform, const FVector& UnloadingVelocity);

	UFUNCTION(BlueprintCallable, Category = "Vessel|Possess", meta = (DisplayName = "Return Possession", ScriptName = "ReturnPossession"))
	inline bool K2_ReturnPossession(UPrimitiveComponent* UnloadingComponent) {
		if (UnloadingComponent) {
			return ReturnPossession(
				UnloadingComponent->GetComponentToWorld(),
				UnloadingComponent->GetPhysicsLinearVelocity()
			);
		}
		return false;
	}


	void SetGhostMode(bool Ghost);
};
