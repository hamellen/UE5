// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player_widget.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API UPlayer_widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* switcher;



	UPROPERTY(meta=(BindWidget))
	class UTextBlock* interaction_dialogue;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* focus_thing;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* current_hp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* number_skeleton;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* total_haveto;
	

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* num_can;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* num_bandage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* homeless_negative;


	//esc button
	

	UPROPERTY(meta = (BindWidget))
	class UButton* button_end;

	UPROPERTY(meta = (BindWidget))
	class UButton* button_back;


	//event
	UFUNCTION(BlueprintCallable)
	void back_normal();
	

	virtual void NativeOnInitialized() override;
};
