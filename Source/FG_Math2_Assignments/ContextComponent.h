// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ContextFlag.h"
#include "UObject/ObjectPtr.h"
#include "ContextComponent.generated.h"

USTRUCT(BlueprintType)
struct FRelatedContext {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    class AActor *Collider;

    UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "EContext"))
    uint8 Context;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FG_MATH2_ASSIGNMENTS_API UContextComponent : public USceneComponent {
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UContextComponent();

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(EditAnywhere)
    bool ShouldRun = false;

    UPROPERTY(EditAnywhere)
    TArray<FRelatedContext> RelatedObjects;

    UFUNCTION(CallInEditor)
    void UpdateContext();

    UFUNCTION()
    uint8 GetContextFor(class AActor *Other);
};
