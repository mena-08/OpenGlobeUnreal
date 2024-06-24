// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomMainCamera.generated.h"

UCLASS()
class OPENGLOBEUNREAL_API ACustomMainCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector current_camera_rotation;

private:
	UPROPERTY(EditAnywhere)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere)
	float rotation_speed;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	void rotateAroundTarget(float DeltaTime);
	void setupInputComponent();

	void rotateCameraX(float axis_values);
	void rotateCameraY(float axis_values);

};
