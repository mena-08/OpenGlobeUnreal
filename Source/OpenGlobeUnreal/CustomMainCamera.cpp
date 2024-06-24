// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMainCamera.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

ACustomMainCamera::ACustomMainCamera()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;

	rotation_speed = 50.0f;
	current_camera_rotation = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void ACustomMainCamera::BeginPlay()
{
	Super::BeginPlay();
	setupInputComponent();

	APlayerController* player_controller = GetWorld()->GetFirstPlayerController();
	if (player_controller) {
		player_controller->SetViewTarget(this);
	}
}

// Called every frame
void ACustomMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	rotateAroundTarget(DeltaTime);
	//rotateAroundTarget(DeltaTime);
}

void ACustomMainCamera::rotateAroundTarget(float DeltaTime)
{
	if (TargetActor) {
		FVector Direction = CameraComponent->GetComponentLocation() - TargetActor->GetActorLocation();
		Direction.Normalize();

		// Create a quaternion for the rotation around the Z axis
		FQuat QuatRotation = FQuat(FRotator(0, rotation_speed * DeltaTime, 0));

		// Rotate the direction vector by the quaternion
		Direction = QuatRotation.RotateVector(Direction);

		// Update the camera's location based on the rotated direction
		FVector NewLocation = TargetActor->GetActorLocation() + Direction * (CameraComponent->GetComponentLocation() - TargetActor->GetActorLocation()).Size();
		CameraComponent->SetWorldLocation(NewLocation);

		// Calculate the new rotation to look at the target
		FRotator NewRotation = (TargetActor->GetActorLocation() - CameraComponent->GetComponentLocation()).Rotation();
		CameraComponent->SetWorldRotation(NewRotation);
	}
}

void ACustomMainCamera::setupInputComponent()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();

	InputComponent->BindAxis("rotateCameraX", this, &ACustomMainCamera::rotateCameraX);
	InputComponent->BindAxis("rotateCameraY", this, &ACustomMainCamera::rotateCameraY);
}

void ACustomMainCamera::rotateCameraX(float axis_values)
{
	current_camera_rotation.X = axis_values*rotation_speed;
}

void ACustomMainCamera::rotateCameraY(float axis_values)
{
	current_camera_rotation.Y = axis_values*rotation_speed;
}