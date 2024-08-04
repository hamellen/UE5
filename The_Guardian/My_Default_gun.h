// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "My_Default_gun.generated.h"

class UNiagaraSystem;

UCLASS()
class THE_GUARDIAN_API AMy_Default_gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMy_Default_gun();

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> main_part;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> grip;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> magazine;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> scope;

	UPROPERTY(EditAnywhere, Category = fire_sfx)
	TObjectPtr<USoundWave> fire_sfx;

	UPROPERTY(EditAnywhere, Category = fire_vfx)
	TObjectPtr<UNiagaraSystem> fire_vfx;

	UPROPERTY(EditAnywhere, Category = reload_sfx)
	TObjectPtr<USoundWave> magazine_out;

	UPROPERTY(EditAnywhere, Category = reload_sfx)
	TObjectPtr<USoundWave> magazine_in;

	UPROPERTY(EditAnywhere, Category = reload_sfx)
	TObjectPtr<USoundWave> stick;


	UPROPERTY(EditAnywhere)
	float gun_damage;


	UPROPERTY(EditAnywhere)
	FName grip_socket;

	UPROPERTY(EditAnywhere)
	FName magazine_socket;

	UPROPERTY(EditAnywhere)
	FName scope_socket;

	UPROPERTY(EditAnywhere)
	FName muzzle_socket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=ammo)
	int current_ammo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ammo)
	int max_ammo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ammo)
	float launch_interval;

	UFUNCTION()
	virtual void Fire(FVector endpoint);

	UFUNCTION()
	virtual void Reload();

	UFUNCTION()
	virtual void reset_gun_ammo();

	UPROPERTY(EditAnywhere,Category=linetrace)
	FVector gun_muzzle_location;

	UPROPERTY(EditAnywhere, Category = linetrace)
	FRotator gun_muzzle_rotation;

	UPROPERTY(EditAnywhere, Category = linetrace)
	FVector gun_foward_vector;


	UPROPERTY(EditAnywhere, Category = reload)
	FVector gun_reload_vector;
};
