// Fill out your copyright notice in the Description page of Project Settings.

#include "ColliderComponent.h"

// Sets default values for this component's properties
UColliderComponent::UColliderComponent() {
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UColliderComponent::BeginPlay() {
    Super::BeginPlay();

    // ...
}

// Called every frame
void UColliderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

FVector UColliderComponent::CheckCollision(UColliderComponent *other) {
    return FVector();
}

bool UColliderComponent::CheckIntersection(UColliderComponent *other) {
    return false;
}
