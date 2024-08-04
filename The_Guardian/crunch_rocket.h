// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "crunch_rocket.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UProjectileMovementComponent;

UCLASS()
class THE_GUARDIAN_API Acrunch_rocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acrunch_rocket();


	UPROPERTY(EditAnywhere, Category = collision)
	TObjectPtr<UCapsuleComponent> capsule;


	UPROPERTY(EditAnywhere, Category = vfx)
	TObjectPtr<UParticleSystem> explosion_vfx;

	UPROPERTY(EditAnywhere, Category = vfx)
	TObjectPtr<UNiagaraSystem> fire_vfx;

	UPROPERTY(EditAnywhere, Category = vfx)
	TObjectPtr<UNiagaraSystem> cluster_vfx;


	UPROPERTY(EditAnywhere, Category = sfx)
	TObjectPtr<USoundWave> rocket_fire_sfx;

	UPROPERTY(EditAnywhere, Category = sfx)
	TObjectPtr<USoundWave> rocket_explosion_sfx;
	
	UPROPERTY(EditAnywhere, Category = volume)
	float volume;

	UPROPERTY(EditAnywhere, Category = damage)
	float base_damage;

	UPROPERTY(EditAnywhere, Category = visual)
	float explosion_size;

	UPROPERTY(EditAnywhere,Category=mesh)
	TObjectPtr<UStaticMeshComponent> rocket_mesh;

	UPROPERTY(EditAnywhere, Category = Niagara)
	TObjectPtr<UNiagaraComponent> cluster_component;

	UPROPERTY(EditAnywhere, Category = projectile)
	TObjectPtr< UProjectileMovementComponent> projectile;

	UFUNCTION()//Ãæµ¹½Ã
	void OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
