// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class OMEN_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	UFUNCTION(BlueprintCallable)
	void MonsterAttack();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable,Category="counter")
	void Counter_Attack(FVector start,FVector target);
	
	UFUNCTION(BlueprintCallable)
	void  Monster_Hited();


	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> sound_monster_attack;


	UFUNCTION()
	void stop_mode(UAnimMontage* Montage,bool bInterrupted);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void PostInitializeComponents();
	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
private:

	UPROPERTY(EditAnywhere,Category=HP, meta = (AllowPrivateAccess = "true"))
	float monster_hp;
	
	UPROPERTY(EditAnywhere, Category = attack, meta = (AllowPrivateAccess = "true"))
	float attack_damage;

	UPROPERTY(EditAnywhere, Category = hited, meta = (AllowPrivateAccess = "true"))
	float hited_damage;
	/*UPROPERTY(EditAnywhere,Category=IS_ATTACK, meta = (AllowPrivateAccess = "true"))
	bool Is_Attack;*/
	
	
	
};
