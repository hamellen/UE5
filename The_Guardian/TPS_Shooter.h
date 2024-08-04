// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyActor.h"
#include "TPS_Shooter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USoldier_SK_Container;
class USoldier_anim;
class UChildActorComponent;
class AMy_Default_gun;
class APlayerController;

UCLASS()
class THE_GUARDIAN_API ATPS_Shooter : public ACharacter
{
	GENERATED_BODY()

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Change_shoot_mode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Reload;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReadyToFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Container, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoldier_SK_Container> soldier_container;

public:
	// Sets default values for this character's properties
	ATPS_Shooter();


	UPROPERTY(EditAnywhere)
	float soldier_pitch;

	UPROPERTY(EditAnywhere)
	float soldier_vertical;

	UPROPERTY(EditAnywhere)
	FName ar_01_socket;

	UPROPERTY(EditAnywhere)
	FName ar_03_socket;

	UPROPERTY(EditAnywhere)
	bool soldier_run;

	UPROPERTY(EditAnywhere)
	int  soldier_weapon_max_ammo;

	UPROPERTY(EditAnywhere)
	int  soldier_test_line_length;

	UPROPERTY(EditAnywhere)
	int  soldier_weapon_current_ammo;

	UPROPERTY(EditAnywhere)
	float  soldier_weapon_interval;

	UPROPERTY(EditAnywhere, Category = HP)
	float hp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<APlayerController> soldier_controller;

	UPROPERTY(EditAnywhere)
	bool soldier_readytofire=false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoldier_anim> soldier_anim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = hand_weapon)
	TObjectPtr<UChildActorComponent> hand_weapon;

	UPROPERTY(EditAnywhere, Category = hand_weapon)
	TObjectPtr<AMy_Default_gun> hand_weapon_obj;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TSubclassOf<AMy_Default_gun> AR_01;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TSubclassOf<AMy_Default_gun> AR_03;

	void Move(const FInputActionValue& Value);

	
	void Look(const FInputActionValue& Value);

	void RunStart(const FInputActionValue& Value);
	void RunEnd(const FInputActionValue& Value);

	void Play_reload(const FInputActionValue& Value);
	void Weapon_Fire_Start(const FInputActionValue& Value);
	void Weapon_Fire_Stop(const FInputActionValue& Value);
	void Regular_weapon_fire();//실질적 발사 구현
	void Change_Fire_mode(const FInputActionValue& Value);

	FVector Caculate_target_point();
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=weapon)
	EWeaponClass current_weapon = EWeaponClass::E_AR_01;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = weapon)
	EShootType current_shoot_type = EShootType::E_SINGLE;


	//void Fire(const FInputActionValue& Value);

	//void Fire_Stop(const FInputActionValue& Value);

	void ChangeAimMode(const FInputActionValue& Value);

	void reset_soldier_ammo();

	FTimerHandle myTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
