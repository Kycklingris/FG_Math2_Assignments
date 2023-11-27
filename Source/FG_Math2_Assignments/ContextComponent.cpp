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
    USphereColliderComponent *ThisCollider =
	GetOwner()->FindComponentByClass<USphereColliderComponent>();

    for (FRelatedContext &RelatedContext : this->RelatedObjects) {
	// Empty the bitmask
	RelatedContext.Context = 0;
	{
	    auto RelatedLocation =
		Cast<AActor>(RelatedContext.Collider)->GetActorLocation();

	    auto LocalSpaceLocation =
		this->GetOwner()->GetActorTransform().InverseTransformPosition(
		    RelatedLocation);

	    if (LocalSpaceLocation.X < 0) {
		RelatedContext.Context |=
		    1 << static_cast<uint8>(EContext::Infront);
	    } else {
		RelatedContext.Context |=
		    1 << static_cast<uint8>(EContext::Behind);
	    }

	    if (LocalSpaceLocation.Y < 0) {
		RelatedContext.Context |=
		    1 << static_cast<uint8>(EContext::ToRight);
	    } else {
		RelatedContext.Context |=
		    1 << static_cast<uint8>(EContext::ToLeft);
	    }

	    if (LocalSpaceLocation.Z < 0) {
		RelatedContext.Context |=
		    1 << static_cast<uint8>(EContext::Above);
	    } else {
		RelatedContext.Context |=
		    1 << static_cast<uint8>(EContext::Below);
	    }
	}

	UColliderComponent *RelatedCollider =
	    RelatedContext.Collider->FindComponentByClass<UColliderComponent>();

	if (ThisCollider->CheckIntersection(RelatedCollider)) {
	    RelatedContext.Context |= 1 << static_cast<uint8>(EContext::Inside);
	}
    }
}

// It no worky
void UContextComponent::PrintContext() {
    this->UpdateContext();

    for (auto RelatedContext : this->RelatedObjects) {

	FString RelativeLocationString = "\"Player\" is ";
	if (RelatedContext.Context & static_cast<uint8>(EContext::Infront)) {
	    RelativeLocationString.Append(TEXT("In front of and "));
	} else if (RelatedContext.Context &
		   static_cast<uint8>(EContext::Behind)) {
	    RelativeLocationString.Append(TEXT("Behind and "));
	}

	if (RelatedContext.Context & static_cast<uint8>(EContext::ToRight)) {
	    RelativeLocationString.Append(TEXT("To the right and "));
	} else if (RelatedContext.Context &
		   static_cast<uint8>(EContext::ToLeft)) {
	    RelativeLocationString.Append(TEXT("To the left and "));
	}

	if (RelatedContext.Context & static_cast<uint8>(EContext::Above)) {
	    RelativeLocationString.Append(TEXT("Above and "));
	} else if (RelatedContext.Context &
		   static_cast<uint8>(EContext::Below)) {
	    RelativeLocationString.Append(TEXT("Below and "));
	}

	if (GEngine)
	    GEngine->AddOnScreenDebugMessage(
		-1, 15.0f, FColor::Yellow, *RelativeLocationString);
    }
}
