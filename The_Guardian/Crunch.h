// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Crunch.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_CrunchMontageEnded);




//struct FDamageEvent;
class UNiagaraSystem;
class ATargetPoint;
UCLASS()
class THE_GUARDIAN_API ACrunch : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACrunch();

	UPROPERTY(EditAnywhere, Category = hited_vfx)
	TObjectPtr<UParticleSystem> hited_vfx;

	UPROPERTY(EditAnywhere, Category = hited_sfx)
	TObjectPtr<USoundBase> hited_sfx;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=sensing_point)
	TObjectPtr<ATargetPoint> central_point;

	UPROPERTY(EditAnywhere,Category=Sensing_radius)
	float sensing_rad;

	UPROPERTY(EditAnywhere,Category=HP)
	float hp;


	FDele_CrunchMontageEnded dele_crunch_montage_ended;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=target_location)
	FVector target_location;

	void Play_jumpattack();
	void Play_meleeattack();

	UFUNCTION()
	void Montage_ended(UAnimMontage* Montage,bool bInterrupted);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
