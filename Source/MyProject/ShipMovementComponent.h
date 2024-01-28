// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Containers\UnrealString.h"
#include "ShipMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UShipMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ScalarAcceleration = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool AllowPhisics = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* VelocityEqualizationActor = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector DeltaVelocity = FVector::ZeroVector;


	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString DebugText;


	FVector PendingAcceleration = FVector::ZeroVector;
	FVector PendingVelocity = FVector::ZeroVector;

	inline static FVector NormalizedVec(FVector Vec, double Tolerance) {
		Vec.Normalize(Tolerance);
		return Vec;
	}
public:

	/**
	 * Default UObject constructor.
	 */
	UShipMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	virtual void AddInputVector(FVector WorldVector, bool bForce = false) override;

	virtual void TickComponent(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	void MoveForwardWithCurrentSpeed(float DeltaTime);

protected:


};
