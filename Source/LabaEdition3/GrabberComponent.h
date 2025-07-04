// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABAEDITION3_API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Use();
	void Grab();
	void Release();
	void Throw();

private:

	UPROPERTY(EditAnywhere)
	float m_GrabbingRange = 200.f;

	UPROPERTY(EditAnywhere)
	float m_ImpulseStrength = 1000.0f;

	UInputComponent* m_InputComponent = nullptr;
	UPhysicsHandleComponent* m_PhysicsHandle = nullptr;
		
};
