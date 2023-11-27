// Fill out your copyright notice in the Description page of Project Settings.

#include "AABBComponent.h"
#include "SphereColliderComponent.h"

FVector UAABBComponent::CheckCollision(UColliderComponent *other) {
    if (other->IsA(UAABBComponent::StaticClass())) {

    } else if (other->IsA(UAABBComponent::StaticClass())) {
    }

    return FVector(0.0f);
}

bool UAABBComponent::CheckIntersection(UColliderComponent *other) {
    if (other->IsA(UAABBComponent::StaticClass())) {

    } else if (other->IsA(USphereColliderComponent::StaticClass())) {
    }

    return false;
}