// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Engine/DataTable.h"
//#include "homeless_ch.h"
#include "Playerable_char.generated.h"



UCLASS()
class OMEN_API APlayerable_char : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerable_char();

	void FowardBackward(float value);
	void LeftRight(float value);
	void Yaw(float value);
	void Pitch(float value);
	//void TurnUp(float value);
	
	void Sprint();
	void Stop_Sprint();
	void Hammer_Attack();

	UFUNCTION(BlueprintCallable,Category="PROP")
	void Bandage();

	UFUNCTION(BlueprintCallable, Category = "PROP")
	void Drink();

	UFUNCTION(BlueprintCallable, Category = "PROP")
	void Syringe();

	UFUNCTION(BlueprintCallable,Category="EDING")
	void ending_start();

	UPROPERTY(VisibleAnywhere, Category = Vertical)
	float input_vertical;

	UPROPERTY(VisibleAnywhere, Category = Horizon)
	float input_horizon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = IsRun)
	bool IS_RUN;

	UPROPERTY(EditAnywhere)
	FString NextLevelName;


	UPROPERTY(EditAnywhere,Category=RUN_SPEED)
	float Sprint_multiplier=2.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = HP)
	float player_hp;

	UPROPERTY()
	TSubclassOf<UUserWidget> ui_class;

	UPROPERTY()
	UUserWidget* first_ui;

	UPROPERTY(VisibleAnywhere)
	int num_morphine;

	UPROPERTY(VisibleAnywhere)
	int num_bandage;
	 
	UPROPERTY(VisibleAnywhere)
	int num_drink;

	UPROPERTY(VisibleAnywhere)
	int num_skeleton;

	UPROPERTY(VisibleAnywhere)
	int havetobone;//°¡Á®¾ß ÇÒ »À °¹¼ö 

	UPROPERTY(EditAnywhere)
	bool is_dialogue;

	UPROPERTY(EditAnywhere)
	bool is_flash;

	

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool is_quest_complete;

	UPROPERTY(VisibleAnywhere)
	FVector last_save_location;


	UPROPERTY(EditAnywhere, Category = HP)
	float recovery_hp;

	UPROPERTY()
	UWorld* world;

	UPROPERTY(EditAnywhere)
	int first_dialogue_index;

	UPROPERTY(EditAnywhere)
	int second_dialogue_index;


	UPROPERTY(EditAnywhere)
	float looking_distance;

	UPROPERTY()
	class UDataTable* first_dialogue;

	UPROPERTY()
	class UDataTable* second_dialogue;


	void speedup();
	void player_hited(float input_damage);
	void player_recovery();
	void lookingfor();
	void change_menu();
	void take();
	void decrease_prop(int index);
	void check_dialogue();
	void check_bone();
	void check_flash();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> sound_flash;
	



	UPROPERTY(VisibleAnywhere, Category = SpringArm, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* spot_light;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* camera;
	
	
};
