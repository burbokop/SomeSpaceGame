// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VesselPossessComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UVesselPossessComponent : public UActorComponent
{
	GENERATED_BODY()

	/** AVessel that owns this component. */
	UPROPERTY(Transient, DuplicateTransient)
	mutable TObjectPtr<class AVessel> VesselOwner;
public:	
	// Sets default values for this component's properties
	UVesselPossessComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Vessel|Components|VesselPossess")
	class AVessel* GetVesselOwner() const;

protected:
	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<class AVessel> PrevPossession;

	// Called when the game starts
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Vessel|Possess")
	virtual bool GivePossessionTo(AController* Controller);

	UFUNCTION(BlueprintCallable, Category = "Vessel|Possess")
	virtual bool ReturnPossession(const FTransform& UnloadingTransform, const FVector& UnloadingVelocity);
};
