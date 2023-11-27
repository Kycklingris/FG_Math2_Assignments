// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ColliderComponent.h"
#include "SphereColliderComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FG_MATH2_ASSIGNMENTS_API USphereColliderComponent
    : public UColliderComponent {
    GENERATED_BODY()

  public:
    virtual FVector CheckCollision(UColliderComponent *other) override;
    virtual bool CheckIntersection(UColliderComponent *other) override;

    UPROPERTY(EditAnywhere)
    float Radius = 0.0f;
};
