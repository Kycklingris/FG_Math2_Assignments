// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EContext : uint8 {
    Infront,
    Behind,
    ToLeft,
    ToRight,
    Above,
    Below,
    Inside,
};