// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AABBComponent.h"
#include "SphereColliderComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntersectsHelper.generated.h"

/**
 *
 */
UCLASS()
class FG_MATH2_ASSIGNMENTS_API UIntersectsHelper
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

  public:
    static float Collision(UAABBComponent *AABB, UAABBComponent *AABB2) {
	return 0.0f;
    };

    static float Collision(
	UAABBComponent *AABB, USphereColliderComponent *Sphere) {
	// https://gamedev.stackexchange.com/questions/156870/how-do-i-implement-a-aabb-sphere-collision

	auto SphereLocation = Sphere->GetOwner()->GetActorLocation();
	auto AABBLocation = AABB->GetOwner()->GetActorLocation();
	FVector Min = FVector(AABBLocation.X - AABB->Size.X,
	    AABBLocation.Y - AABB->Size.Y, AABBLocation.Z - AABB->Size.Z);
	FVector Max = FVector(AABBLocation.X + AABB->Size.X,
	    AABBLocation.Y + AABB->Size.Y, AABBLocation.Z + AABB->Size.Z);

	if (GEngine)
	    GEngine->AddOnScreenDebugMessage(
		-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Min[0]));

	if (GEngine)
	    GEngine->AddOnScreenDebugMessage(
		-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Max[0]));

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++) {
	    // for each axis count any excess distance outside box extents.
	    float v = SphereLocation[i];
	    if (v < Min[i]) {
		sqDist += (Min[i] - v) * (Min[i] - v);
	    }
	    if (v > Max[i]) {
		sqDist += (v - Max[i]) * (v - Max[i]);
	    }
	}

	return sqDist - (Sphere->Radius * Sphere->Radius);
    };

    static float Collision(
	USphereColliderComponent *Sphere, USphereColliderComponent *Sphere2) {
	auto OneLocation = Sphere->GetOwner()->GetActorLocation();
	auto TwoLocation = Sphere2->GetOwner()->GetActorLocation();

	return 0.0f;
    };
};