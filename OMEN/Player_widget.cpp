// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UPlayer_widget::back_normal()
{
	switcher->SetActiveWidgetIndex(0);
	
}

void UPlayer_widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	

	/*button_join = Cast<UButton>(GetWidgetFromName(TEXT("button_join")));
	button_end = Cast<UButton>(GetWidgetFromName(TEXT("button_end")));
	interaction_dialogue = Cast<UTextBlock>(GetWidgetFromName(TEXT("interaction_dialogue")));*/
}
