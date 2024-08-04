// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Soldier_particle_module.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THE_GUARDIAN_API USoldier_particle_module : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category=fire_sfx)
	TObjectPtr<USoundWave> fire_sfx;

	UPROPERTY(EditAnywhere, Category = fire_vfx)
	TObjectPtr<UNiagaraSystem> fire_vfx;

	UPROPERTY(EditAnywhere, Category = reload_sfx)
	TObjectPtr<USoundWave> magazine_out;

	UPROPERTY(EditAnywhere, Category = reload_sfx)
	TObjectPtr<USoundWave> magazine_in;

	UPROPERTY(EditAnywhere, Category = reload_sfx)
	TObjectPtr<USoundWave> stick;

public:	
	// Sets default values for this component's properties
	USoldier_particle_module();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
