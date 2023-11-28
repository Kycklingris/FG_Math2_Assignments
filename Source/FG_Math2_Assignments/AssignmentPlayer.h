// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Templates/SubclassOf.h"
#include "AssignmentPlayer.generated.h"

UCLASS()
class FG_MATH2_ASSIGNMENTS_API AAssignmentPlayer : public APawn {
    GENERATED_BODY()

  public:
    // Sets default values for this pawn's properties
    AAssignmentPlayer();

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector InputVector;

    UPROPERTY(VisibleAnywhere)
    float InputAlpha = 0.0f;

    UPROPERTY(EditAnywhere)
    float Speed = 10.0f;

    UPROPERTY(VisibleAnywhere)
    float TimeSince = 0.0f;

	UPROPERTY(VisibleAnywhere)
	bool IsOnGround = false;

	UPROPERTY(VisibleAnywhere)
	float GravityVelocity = 0.0f;

	UPROPERTY(EditAnywhere)
	float Gravity = 10.0f;

	UPROPERTY(VisibleAnywhere)
	float CameraShakeTimeLeft = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CameraOffset;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent *Sphere;

	UPROPERTY(EditAnywhere)
	class USphereColliderComponent *SphereCollider;

	UPROPERTY(EditAnywhere)
	class UCameraComponent *Camera;

	UPROPERTY(EditAnywhere)
	class UContextComponent *Context;

      public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
	    class UInputComponent *PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void E();

	void CheckCollision();

	void ShakeCamera(float DeltaTime);

	UPROPERTY(EditAnywhere)
	TArray<class AActor *> CollisionObjects;

	UPROPERTY(EditAnywhere)
	TArray<class AActor *> BackstabBoxes;
};
