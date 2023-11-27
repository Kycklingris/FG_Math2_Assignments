// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereColliderComponent.h"
#include "AABBComponent.h"
#include "IntersectsHelper.h"

FVector USphereColliderComponent::CheckCollision(UColliderComponent *other) {
    return FVector();
}

bool USphereColliderComponent::CheckIntersection(UColliderComponent *other) {
    if (other->IsA(UAABBComponent::StaticClass())) {
	auto Val =
	    UIntersectsHelper::Collision(Cast<UAABBComponent>(other), this);
	if (GEngine)
	    GEngine->AddOnScreenDebugMessage(
		-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Val));
	if (Val < 0.0f) {
	    return true;
	}
    } else if (other->IsA(USphereColliderComponent::StaticClass())) {
    }

    return false;
}