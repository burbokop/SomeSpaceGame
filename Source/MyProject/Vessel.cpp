// Fill out your copyright notice in the Description page of Project Settings.


#include "Vessel.h"

// Sets default values
AVessel::AVessel()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

UPrimitiveComponent* AVessel::GetPrimitiveRootComponent() const {
	if (auto PrimitiveRootComponent = Cast<UPrimitiveComponent>(GetRootComponent())) {
		return PrimitiveRootComponent;
	} else {
		const auto& text = FString::Printf(
			TEXT("Vessel %s root component %s unexpected type %s. expected PrimitiveComponent"),
			*GetDebugName(this),
			*(GetRootComponent() ? GetRootComponent()->GetName() : "NULL"),
			*(GetRootComponent() ? GetRootComponent()->GetClass()->GetName() : "NULL")
		);
		FMessageLog(FName("PIE")).Error(FText::FromString(text));
		return nullptr;
	}
}

UVesselRotationComponent* AVessel::GetRotationComponent() const {
	return FindComponentByClass<UVesselRotationComponent>();
}

UVesselPossessComponent* AVessel::GetPossessComponent() const {
	return FindComponentByClass<UVesselPossessComponent>();
}

void AVessel::AddYawInput(double Yaw, bool bForce) {
	if (auto Component = GetRotationComponent()) {
		Component->AddYawInput(Yaw, bForce);
	} else {
		AddControllerYawInput(Yaw);
	}
}

void AVessel::AddPitchInput(double Pitch, bool bForce) {
	if (auto Component = GetRotationComponent()) {
		Component->AddPitchInput(Pitch, bForce);
	} else {
		AddControllerPitchInput(Pitch);
	}
}

void AVessel::AddRollInput(double Roll, bool bForce) {
	if (auto Component = GetRotationComponent()) {
		Component->AddRollInput(Roll, bForce);
	} else {
		AddControllerRollInput(Roll);
	}
}

inline bool AVessel::GivePossessionTo(AController* Ctrl) {
	if (const auto& Component = GetPossessComponent()) {
		return Component->GivePossessionTo(Ctrl);
	} else {
		const auto& text = FString::Printf(
			TEXT("GivePossessionTo called on %s but PossessComponent not found."),
			*GetDebugName(this)
		);
		FMessageLog(FName("PIE")).Error(FText::FromString(text));
		UE_LOG(LogTemp, Error, TEXT("GivePossessionTo: retfalse"));
		return false;
	}
}

void AVessel::SetGhostMode(bool Ghost) {
	SetActorHiddenInGame(Ghost);
	SetActorEnableCollision(!Ghost);
}

// Called when the game starts or when spawned
void AVessel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVessel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


UFUNCTION(BlueprintCallable, Category = "Vessel|Possess")
bool AVessel::ReturnPossession(const FTransform& UnloadingTransform, const FVector& UnloadingVelocity) {
	if (const auto& Component = GetPossessComponent()) {
		return Component->ReturnPossession(UnloadingTransform, UnloadingVelocity);
	} else {
		const auto& text = FString::Printf(
			TEXT("ReturnPossession called on %s but PossessComponent not found."),
			*GetDebugName(this)
		);
		FMessageLog(FName("PIE")).Error(FText::FromString(text));
		return false;
	}
}

