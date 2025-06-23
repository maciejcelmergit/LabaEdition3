// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	m_InputComponent = GetOwner()->GetComponentByClass<UInputComponent>();

	if (m_InputComponent)
	{
		m_InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberComponent::Use);
		m_InputComponent->BindAction("Throw", IE_Pressed, this, &UGrabberComponent::Throw);
	}

	m_PhysicsHandle = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();

	if (!m_PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("UPhysicsHandleComponent required"));
	}
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_PhysicsHandle && m_PhysicsHandle->GetGrabbedComponent())
	{
		FVector Start;
		FVector End;
		FRotator CameraRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
		End = Start + CameraRotation.Vector() * m_GrabbingRange;

		m_PhysicsHandle->SetTargetLocationAndRotation(End, CameraRotation);
	}
}

void UGrabberComponent::Use()
{
	if (m_PhysicsHandle && m_PhysicsHandle->GetGrabbedComponent())
	{
		Release();
	}
	else if (m_PhysicsHandle)
	{
		Grab();
	}
}

void UGrabberComponent::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabing item!"));

	FHitResult Result;

	FVector Start;
	FVector End;
	FRotator CameraRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
	End = Start + CameraRotation.Vector() * m_GrabbingRange;

	GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.0f, 0, 5.0f);

	if (Result.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Item found: %s"), *Result.GetActor()->GetHumanReadableName());

		UPrimitiveComponent* Component = Result.GetComponent();

		m_PhysicsHandle->GrabComponentAtLocationWithRotation(Component, FName(),
			Component->GetComponentLocation(), Component->GetComponentRotation());
	}
}

void UGrabberComponent::Release()
{
	m_PhysicsHandle->ReleaseComponent();
}

void UGrabberComponent::Throw()
{
	if (m_PhysicsHandle && m_PhysicsHandle->GetGrabbedComponent())
	{
		UPrimitiveComponent* Component = m_PhysicsHandle->GetGrabbedComponent();

		FVector Impulse;

		FVector Start;
		FRotator CameraRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);

		Impulse = CameraRotation.Vector() * m_ImpulseStrength;

		m_PhysicsHandle->ReleaseComponent();

		Component->AddImpulse(Impulse);
	}
}

