// Fill out your copyright notice in the Description page of Project Settings.

#include "AssignmentPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Colliders/SphereColliderComponent.h"
#include "Colliders/AABBComponent.h"
#include "Colliders/IntersectsHelper.h"
#include "ContextComponent.h"
#include "Engine/EngineTypes.h"
#include "EasingFunctions.h"
#include "ContextFlag.h"
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

    // Interpolate the movement alpha
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

    if (!IsOnGround) {
	GravityVelocity += Gravity * DeltaTime;
    }

    auto CurrentLocation = GetActorLocation();
    CurrentLocation += InputVector * Speed * DeltaTime * InputAlpha;
    CurrentLocation += FVector(0.0f, 0.0f, -GravityVelocity);
    SetActorLocation(CurrentLocation, false, nullptr, ETeleportType::None);

    CheckCollision();

    ShakeCamera(DeltaTime);
}

// Called to bind functionality to input
void AAssignmentPlayer::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAssignmentPlayer::Jump() {}

// Runs on well, the E key.
void AAssignmentPlayer::E() {
    for (AActor *BackstabBox : BackstabBoxes) {
	if (!IsValid(BackstabBox)) {
	    continue;
	}

	auto Bitflags = Context->GetContextFor(BackstabBox);

	// Would have liked to check both flags at the same time, but well,
	// didn't get it to work.
	if (Bitflags & 1 << static_cast<uint8>(EContext::Behind) &&
	    Bitflags & 1 << static_cast<uint8>(EContext::Inside)) {
	    if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		    TEXT("OMG! Super interesting \"backstab\""));
	}
    }
}

void AAssignmentPlayer::CheckCollision() {
    IsOnGround = false;

    for (AActor *CollisionObject : CollisionObjects) {
	UAABBComponent *Collider =
	    CollisionObject->FindComponentByClass<UAABBComponent>();

	float Val = UIntersectsHelper::Collision(
	    Cast<UAABBComponent>(Collider), SphereCollider);

	if (Val >= 0.0f) {
	    continue;
	}

	auto OtherLocation = CollisionObject->GetActorLocation();
	auto ThisLocation = GetActorLocation();

	// auto OffsetDirection = OtherLocation - ThisLocation;
	// OffsetDirection.Normalize();

	FVector OffsetDirection = FVector(0.0f, 0.0f, 1.0f);

	OffsetDirection *= -Val;

	ThisLocation += OffsetDirection;

	SetActorLocation(ThisLocation, false, nullptr, ETeleportType::None);

	IsOnGround = true;

	// If impact is severe enough start screen shake
	if (GravityVelocity > 5.0f) {
	    CameraShakeTimeLeft = 0.5f;
	}
	GravityVelocity = 0.0f;
    }
}

void AAssignmentPlayer::ShakeCamera(float DeltaTime) {
    if (CameraShakeTimeLeft < 0.0f) {
	Camera->SetRelativeLocation_Direct(CameraOffset);
	return;
    }

    CameraShakeTimeLeft -= DeltaTime;

    auto Z =
	UEasingFunctions::OneDimNoise((0.5f - CameraShakeTimeLeft) * 10.0f);

    auto TmpCameraOffset = CameraOffset;
    TmpCameraOffset.Z += Z * 2.0f;

    Camera->SetRelativeLocation_Direct(TmpCameraOffset);
}