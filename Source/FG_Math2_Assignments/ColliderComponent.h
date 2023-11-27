// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColliderComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FG_MATH2_ASSIGNMENTS_API UColliderComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UColliderComponent();

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction) override;

    virtual bool CheckIntersection(UColliderComponent *other);

    virtual FVector CheckCollision(UColliderComponent *other);
};
