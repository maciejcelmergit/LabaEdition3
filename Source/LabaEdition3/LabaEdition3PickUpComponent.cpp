// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabaEdition3PickUpComponent.h"

ULabaEdition3PickUpComponent::ULabaEdition3PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void ULabaEdition3PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &ULabaEdition3PickUpComponent::OnSphereBeginOverlap);
}

void ULabaEdition3PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ALabaEdition3Character* Character = Cast<ALabaEdition3Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
