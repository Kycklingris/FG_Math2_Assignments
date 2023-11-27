// Fill out your copyright notice in the Description page of Project Settings.

#include "ContextComponent.h"
#include "ContextFlag.h"
#include "ColliderComponent.h"
#include "Colliders/SphereColliderComponent.h"
#include "Colliders/IntersectsHelper.h"

// Sets default values for this component's properties
UContextComponent::UContextComponent() {
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    bTickInEditor = false;

    // ...
}

// Called when the game starts
void UContextComponent::BeginPlay() {
    Super::BeginPlay();

    // ...
}

// Called every frame
void UContextComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UContextComponent::UpdateContext() {
    for (FRelatedContext &RelatedContext : this->RelatedObjects) {
	RelatedContext.Context = GetContextFor(RelatedContext.Collider);
    }
}

uint8 UContextComponent::GetContextFor(AActor *Other) {
    USphereColliderComponent *ThisCollider =
	GetOwner()->FindComponentByClass<USphereColliderComponent>();

    // Empty the bitmask
    uint8 Context = 0;
    {
	auto RelatedLocation = Cast<AActor>(Other)->GetActorLocation();

	auto LocalSpaceLocation =
	    this->GetOwner()->GetActorTransform().InverseTransformPosition(
		RelatedLocation);

	if (LocalSpaceLocation.X < 0) {
	    Context |= 1 << static_cast<uint8>(EContext::Infront);
	} else {
	    Context |= 1 << static_cast<uint8>(EContext::Behind);
	}

	if (LocalSpaceLocation.Y < 0) {
	    Context |= 1 << static_cast<uint8>(EContext::ToRight);
	} else {
	    Context |= 1 << static_cast<uint8>(EContext::ToLeft);
	}

	if (LocalSpaceLocation.Z < 0) {
	    Context |= 1 << static_cast<uint8>(EContext::Above);
	} else {
	    Context |= 1 << static_cast<uint8>(EContext::Below);
	}
    }

    UColliderComponent *RelatedCollider =
	Other->FindComponentByClass<UColliderComponent>();

    if (ThisCollider->CheckIntersection(RelatedCollider)) {
	Context |= 1 << static_cast<uint8>(EContext::Inside);
    }

    return Context;
}