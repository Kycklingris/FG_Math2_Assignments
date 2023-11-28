// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EasingFunctions.generated.h"

/**
 *
 */
UCLASS()
class FG_MATH2_ASSIGNMENTS_API UEasingFunctions
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

  public:
    // https://stackoverflow.com/questions/13462001/ease-in-and-ease-out-animation-formula
    static float BezierBlend(float t) { return t * t * (3.0f - 2.0f * t); }

    // https://stackoverflow.com/questions/8798771/perlin-noise-for-1d
    // Seemed to be good enough considering I only want I dimension.
    static float OneDimNoise(float x) {
	return UKismetMathLibrary::Sin(2 * x) +
	       UKismetMathLibrary::Sin(UKismetMathLibrary::GetPI() * x);
    }
};