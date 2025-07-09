// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, AActor*, Actor);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABAEDITION3_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetCurrentHealth();

	UFUNCTION(BlueprintPure)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float maxHealth);

	UFUNCTION(BlueprintCallable)
	void Heal(float healAmount);

	UFUNCTION(BlueprintCallable)
	void Damage(float damageAmount);

	UFUNCTION(BlueprintPure)
	bool IsDead();

	UFUNCTION(BlueprintCallable)
	void Kill();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedDelegate OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeath;

protected:

	UPROPERTY(EditDefaultsOnly)
	float CurrentHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;
};
