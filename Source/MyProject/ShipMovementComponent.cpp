// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipMovementComponent.h"

UShipMovementComponent::UShipMovementComponent(const FObjectInitializer& ObjectInitializer) 
    : UPawnMovementComponent(ObjectInitializer) {}

void UShipMovementComponent::AddInputVector(FVector WorldVector, bool bForce) {
    if (!IsMoveInputIgnored() || bForce) {
        const auto& Prim = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
        if (Prim && AllowPhisics) {

            //if (GEngine) {
            //    const auto& msg = FString::Printf(TEXT("v: %s"), *WorldVector.ToString());
            //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, msg);
            //}
            //Prim->AddForce(WorldVector * 100000);
            //Prim->SetPhysicsLinearVelocity(WorldVector * 20, false);
        }
        PendingAcceleration += ScalarAcceleration * WorldVector;
    }
}

static const AActor* root_actor(const AActor* A) {
    if (A->IsChildActor()) {
        return root_actor(A->GetParentActor());
    } else {
        return A;
    }
}
static AActor* root_actor_mut(AActor* A) {
    if (A->IsChildActor()) {
        return root_actor_mut(A->GetParentActor());
    } else {
        return A;
    }
}



void UShipMovementComponent::TickComponent(
    float DeltaTime,
    enum ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) { return; }


    if (VelocityEqualizationActor) {
        VelocityEqualizationActor = root_actor_mut(VelocityEqualizationActor);

        if (VelocityEqualizationActor->GetRootComponent()) {
            DebugText = VelocityEqualizationActor->GetRootComponent()->GetName();
        } else {
            DebugText = "NULL";
        }

        const auto& TargetVelocity = VelocityEqualizationActor->GetVelocity();

        
        DeltaVelocity = TargetVelocity - GetOwner()->GetVelocity();
        if (PendingAcceleration.IsZero()) {
            AddInputVector(NormalizedVec(DeltaVelocity, 1.), true);
        }
    }

    PendingVelocity += PendingAcceleration;
    PendingAcceleration = FVector::ZeroVector;

    const auto& Prim = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    if (Prim && AllowPhisics) {
        Prim->SetPhysicsLinearVelocity(PendingVelocity * 20, false);
        return; 
    }

    MoveUpdatedComponent(PendingVelocity, this->PawnOwner->GetViewRotation(), false);
    UpdateComponentVelocity();

    /*
    if (CheckState(EShipMovementState::Accelerating)) {
        if (CurrentSpeed < CurrentMaxSpeed) {
            CurrentSpeed += Acceleration;
            AccelerationPath += CurrentSpeed * DeltaTime;
        }
        else {
            CurrentSpeed = CurrentMaxSpeed;
            RemoveState(EShipMovementState::Accelerating);
        }
    }
    else if (CheckState(EShipMovementState::Braking)) {
        if (CurrentSpeed > 0.0f) {
            CurrentSpeed -= Acceleration;
            DeaccelerationPath += CurrentSpeed * DeltaTime;
        }
        else {
            CurrentSpeed = 0.0f;
            CurrentMaxSpeed = MaxSpeed;
            RemoveState(EShipMovementState::Braking);
            RemoveState(EShipMovementState::Moving);
        }
    }
    else if (CheckState(EShipMovementState::SpeedDecreasing)) {
        if (CurrentSpeed > CurrentMaxSpeed) {
            CurrentSpeed -= Acceleration;
            DeaccelerationPath += CurrentSpeed * DeltaTime;
        }
        else {
            CurrentSpeed = CurrentMaxSpeed;
            RemoveState(EShipMovementState::SpeedDecreasing);
        }
    } if (CheckState(EShipMovementState::Moving) || CheckState(EShipMovementState::Turning)) {
        MoveForwardWithCurrentSpeed(DeltaTime);
    }
    */
}

void UShipMovementComponent::MoveForwardWithCurrentSpeed(float DeltaTime) {
    //Velocity = UpdatedComponent->GetForwardVector() * CurrentSpeed * DeltaTime;
    //MoveUpdatedComponent(Velocity, AcceptedRotator, false);
    UpdateComponentVelocity();
}

