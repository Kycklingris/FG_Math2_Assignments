// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunctions.generated.h"

/**
 *
 */
UCLASS()
class FG_MATH2_ASSIGNMENTS_API UEasingFunctions
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

  public:
    static float BezierBlend(float t) { return t * t * (3.0f - 2.0f * t); }
};