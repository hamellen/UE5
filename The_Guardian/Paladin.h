// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyActor.h"
#include "Paladin.generated.h"

class UNiagaraSystem;
class  Acrunch_rocket;

DECLARE_MULTICAST_DELEGATE(FDele_PaladinMontageEnded);

UCLASS()
class THE_GUARDIAN_API APaladin : public ACharacter
{

	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APaladin();

	UPROPERTY(EditAnywhere, Category = hited)
	TObjectPtr<UParticleSystem> hited_vfx;


	UPROPERTY(EditAnywhere, Category = hited_sfx)
	TObjectPtr<USoundBase> hited_sfx;

	UPROPERTY(EditAnywhere,Category=HP)
	float hp;

	UPROPERTY(EditAnywhere, Category = WAKEUP)
	int wakeup_figure;

	UPROPERTY(EditAnywhere,Category=mode)
	EPalain_mode mode= EPalain_mode::E_SLEEP;

	UPROPERTY(EditAnywhere, Category = Sensing_radius)
	float sensing_rad;

	UPROPERTY(EditAnywhere, Category = HP)
	bool is_targeted;

	UPROPERTY(EditAnywhere)
	FVector shooter_location;

	UPROPERTY(EditAnywhere, Category = HP)
	bool is_active;

	UPROPERTY(EditAnywhere, Category = wake_sfx)
	TObjectPtr<USoundBase> wake_up;

	UPROPERTY(EditAnywhere, Category = rocket)
	TSubclassOf<Acrunch_rocket> rocket_class;

	void play_attack();

	FDele_PaladinMontageEnded dele_paladin_montage_ended;

	UFUNCTION()
	void Montage_ended(UAnimMontage* Montage, bool bInterrupted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
