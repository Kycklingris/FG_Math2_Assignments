// Fill out your copyright notice in the Description page of Project Settings.

#include "AssignmentPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Colliders/SphereColliderComponent.h"
#include "ContextComponent.h"
#include "Engine/EngineTypes.h"
#include "EasingFunctions.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAssignmentPlayer::AAssignmentPlayer() {
    // Set this pawn to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
    RootComponent = Sphere;

    SphereCollider =
	CreateDefaultSubobject<USphereColliderComponent>(TEXT("Collider"));

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(Sphere);

    Context = CreateDefaultSubobject<UContextComponent>(TEXT("Context"));
    Context->SetupAttachment(Sphere);
}

// Called when the game starts or when spawned
void AAssignmentPlayer::BeginPlay() {
    Super::BeginPlay();
    Camera->SetRelativeLocation_Direct(CameraOffset);
}

// Called every frame
void AAssignmentPlayer::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

	// True if there movement should be happening
    bool Input = !InputVector.IsNearlyZero(0.001);

    if (Input && InputAlpha < 0.999f) {
	if (TimeSince < 0.0f) {
	    TimeSince = 0.0f;
	}
	TimeSince += DeltaTime;
	InputAlpha = UEasingFunctions::BezierBlend(TimeSince);
    } else if (!Input && InputAlpha > 0.001f) {
	if (TimeSince > 1.0f) {
	    TimeSince = 1.0f;
	}
	TimeSince -= DeltaTime;
	InputAlpha = UEasingFunctions::BezierBlend(TimeSince);
    }

    auto CurrentLocation = GetActorLocation();
    CurrentLocation += InputVector * Speed * DeltaTime * InputAlpha;
    SetActorLocation(CurrentLocation, false, nullptr, ETeleportType::None);
}

// Called to bind functionality to input
void AAssignmentPlayer::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAssignmentPlayer::Jump() {}

void AAssignmentPlayer::E() {}