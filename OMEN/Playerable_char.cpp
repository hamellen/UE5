// Fill out your copyright notice in the Description page of Project Settings.


#include "Playerable_char.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/Color.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Homeless_Ai.h"
#include "MyMelee.h"
#include "Kismet/GameplayStatics.h"
#include "Styling/SlateColor.h"
#include "player_animinstance.h"
#include "Engine/DataTable.h"
#include "Homeless_Ai.h"
#include "Components/SpotLightComponent.h"
#include "displayname.h"
#include "jumpscare_monster.h"
#include "homeless_ch.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework//CharacterMovementComponent.h"
#include "Player_widget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
// Sets default values
APlayerable_char::APlayerable_char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	spot_light = CreateDefaultSubobject<USpotLightComponent>(TEXT("SPOTLIGHT"));
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	NextLevelName = FString(TEXT("MAINMENU"));
	sound_flash = LoadObject<USoundWave>(nullptr,TEXT("SoundWave'/Game/SFX/flashlight-clicking-on-105809.flashlight-clicking-on-105809'"));
	
	num_morphine = 0;
	num_bandage = 0;
	num_drink = 0;
	num_skeleton = 0;
	havetobone = 5;
	first_dialogue_index = 0;
	second_dialogue_index = 0;
	
	


	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);
	player_hp = 100.f;
	recovery_hp = 20.f;
	looking_distance = 2000.f;
	world = GetWorld();
	is_dialogue = false;
	is_flash = false;
	is_quest_complete = false;
	
	static ConstructorHelpers::FClassFinder<UPlayer_widget>ui(TEXT("WidgetBlueprint'/Game/WIDGET/first_ui.first_ui_C'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK(TEXT("SkeletalMesh'/Game/DetectiveCharacter/Character/Skeleton_UE4/SK_BodyDetective_02_UE4.SK_BodyDetective_02_UE4'"));
	static ConstructorHelpers::FObjectFinder<UDataTable>first(TEXT("DataTable'/Game/dialogue_list_first.dialogue_list_first'"));
	static ConstructorHelpers::FObjectFinder<UDataTable>second(TEXT("DataTable'/Game/dialogue_list_second.dialogue_list_second'"));

	if (first.Succeeded()) {
		first_dialogue = first.Object;
	}

	if (second.Succeeded()) {
		second_dialogue = second.Object;
	}

	if (SK.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK.Object);
	}

	spot_light->SetupAttachment(GetMesh(), FName(TEXT("head")));
	camera->SetupAttachment(spot_light);
	camera->bUsePawnControlRotation = true;
	if (ui.Succeeded()) {

		ui_class = ui.Class;
		first_ui = CreateWidget(GetWorld(), ui_class);
		if (first_ui) {
			first_ui->AddToViewport();
		}
	}

	//auto widget = Cast<UPlayer_widget>(first_ui);
	//widget->total_haveto->SetText(FText::FromString(FString::Printf(TEXT("%d"), havetobone)));

}

void APlayerable_char::FowardBackward(float value)
{
	if (!is_dialogue) {
		input_vertical = value;
		if (value == 0.f) {
			return;
		}

		AddMovementInput(GetActorForwardVector(), value);
	}

}

void APlayerable_char::LeftRight(float value)
{

	if (!is_dialogue) {
		input_horizon = value;
		if (value == 0.f) {
			return;
		}

		AddMovementInput(GetActorRightVector(), value);
	}
	
}

void APlayerable_char::Yaw(float value)
{
	if (!is_dialogue) {
		AddControllerYawInput(value);
	}

	
}

void APlayerable_char::Pitch(float value)
{
	if (!is_dialogue) {
		AddControllerPitchInput(value);
	}
}

void APlayerable_char::Sprint()
{
	if (!is_dialogue) {
		IS_RUN = true;
		GetCharacterMovement()->MaxWalkSpeed *= Sprint_multiplier;

		UE_LOG(LogTemp, Warning, TEXT("RUNNING"));
	}

	
	
}

void APlayerable_char::Stop_Sprint()
{
	if (!is_dialogue) {
		IS_RUN = false;
		GetCharacterMovement()->MaxWalkSpeed /= Sprint_multiplier;
		UE_LOG(LogTemp, Warning, TEXT(" NOT RUNNING"));
	}

}

void APlayerable_char::Hammer_Attack()
{
	if (!is_dialogue) {
		auto animinstance = Cast<Uplayer_animinstance>(GetMesh()->GetAnimInstance());
		if (animinstance) {

			animinstance->PlayHammerAttack();
		}
	}
	
}

void APlayerable_char::Bandage()
{
	if (num_bandage > 0 && !is_dialogue) {

		auto animinstance = Cast<Uplayer_animinstance>(GetMesh()->GetAnimInstance());
		if (animinstance) {
			animinstance->PlayBandageMotion();
		}
	}
}

void APlayerable_char::Drink()
{
	if (num_drink > 0 && !is_dialogue) {
		auto animinstance = Cast<Uplayer_animinstance>(GetMesh()->GetAnimInstance());
		if (animinstance) {
			animinstance->PlayDrinkMotion();
		}
	}
}

void APlayerable_char::Syringe()
{

	if (num_morphine > 0 && !is_dialogue) {

		auto animinstance = Cast<Uplayer_animinstance>(GetMesh()->GetAnimInstance());
		if (animinstance) {
			animinstance->PlaySyringeMotion();
		}
	}
}

void APlayerable_char::ending_start()//이때부터 글씨가 붉은색으로 변경
{
		
		TArray<FDialogue_list*> second_list;
		second_dialogue->GetAllRows<FDialogue_list>(TEXT("GetAllRows"), second_list);
		auto widget = Cast<UPlayer_widget>(first_ui);
		widget->switcher->SetActiveWidgetIndex(2);
		widget->homeless_negative->SetText(FText::FromString(FString::Printf(TEXT("%s"), *second_list[second_dialogue_index]->line_dialogue)));
		second_dialogue_index++;
	
	
}



// Called when the game starts or when spawned
void APlayerable_char::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerable_char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerable_char::speedup()
{
	GetCharacterMovement()->MaxWalkSpeed += 10.f;
}

void APlayerable_char::player_hited(float input_damage)
{
	UE_LOG(LogTemp, Warning, TEXT("player_hited"));
	player_hp -= input_damage;
	if (player_hp > 0) {
		auto widget = Cast<UPlayer_widget>(first_ui);
		const FString health = FString::Printf(TEXT("%f"), player_hp);
		widget->current_hp->SetText(FText::FromString(health));
	}
	else {//플레이어 사망
		UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("jumpscare_level")));
	}
}

void APlayerable_char::player_recovery()
{
	player_hp += recovery_hp;

	auto widget = Cast<UPlayer_widget>(first_ui);
	const FString health = FString::Printf(TEXT("%f"), player_hp);
	widget->current_hp->SetText(FText::FromString(health));
}

void APlayerable_char::lookingfor()
{
	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool hited=world->LineTraceSingleByChannel(result, 
		camera->GetComponentLocation(), 
		camera->GetComponentLocation()+(camera->GetForwardVector()* looking_distance),
		ECC_Visibility, params);
	
	if (hited) {
		if (UKismetSystemLibrary::DoesImplementInterface(result.GetActor(), Udisplayname::StaticClass())) {
			auto widget = Cast<UPlayer_widget>(first_ui);
			FString looking;
			if (result.GetActor()->ActorHasTag(FName("can"))) {
				looking = FString::Printf(TEXT("boot up can(press e)"));
			}
			else if (result.GetActor()->ActorHasTag(FName("bandage"))) {
				looking = FString::Printf(TEXT("bandage(press e)"));
			}
			else if (result.GetActor()->ActorHasTag(FName("corpse"))) {
				looking = FString::Printf(TEXT("corpse(press e)"));
			}
			
			
			widget->focus_thing->SetText(FText::FromString(looking));
		}
		else {
			auto widget = Cast<UPlayer_widget>(first_ui);
			
			widget->focus_thing->SetText(FText::FromString(FString::Printf(TEXT(""))));
		}
	}
	
}

void APlayerable_char::change_menu()//esc 누를시 메뉴 변화 
{
	auto widget = Cast<UPlayer_widget>(first_ui);

	widget->switcher->SetActiveWidgetIndex(1);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
	}


}

void APlayerable_char::take()
{
	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	auto widget = Cast<UPlayer_widget>(first_ui);
	bool hited = world->LineTraceSingleByChannel(result,
		camera->GetComponentLocation(),
		camera->GetComponentLocation() + (camera->GetForwardVector() * looking_distance),
		ECC_Visibility, params);

	if (hited) {
		if (UKismetSystemLibrary::DoesImplementInterface(result.GetActor(), Udisplayname::StaticClass())) {
			
			if (result.GetActor()->ActorHasTag(FName("can"))) {
				result.GetActor()->Destroy();
				num_drink++;
				widget->num_can->SetText(FText::FromString(FString::Printf(TEXT("%d"),num_drink)));
			}
			else if (result.GetActor()->ActorHasTag(FName("bandage"))) {
				result.GetActor()->Destroy();
				num_bandage++;
				widget->num_bandage->SetText(FText::FromString(FString::Printf(TEXT("%d"), num_bandage)));
			}
			
			else if (result.GetActor()->ActorHasTag(FName("corpse"))) {
				result.GetActor()->Destroy();
				num_skeleton++;
				widget->number_skeleton->SetText(FText::FromString(FString::Printf(TEXT("%d"), num_skeleton)));
				check_bone();
			}
		}
	}
	
}

void APlayerable_char::decrease_prop(int index)//1-can 2-bandage 3-syringe
{
	auto widget = Cast<UPlayer_widget>(first_ui);

	switch (index)
	{
	case 1:
		widget->num_can->SetText(FText::FromString(FString::Printf(TEXT("%d"), num_drink)));
		break;

	case 2:
		widget->num_bandage->SetText(FText::FromString(FString::Printf(TEXT("%d"), num_bandage)));
		break;


	}


}

void APlayerable_char::check_dialogue()
{
	
	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	TArray<FDialogue_list*> first_list;
	first_dialogue->GetAllRows<FDialogue_list>(TEXT("GetAllRows"), first_list);
	auto widget = Cast<UPlayer_widget>(first_ui);
	bool hited = world->LineTraceSingleByChannel(result,
		camera->GetComponentLocation(),
		camera->GetComponentLocation() + (camera->GetForwardVector() * looking_distance),
		ECC_Visibility, params);

	if (is_quest_complete) {//미션 성공한상태에서 


		TArray<FDialogue_list*> second_list;
		second_dialogue->GetAllRows<FDialogue_list>(TEXT("GetAllRows"), second_list);

		if (second_dialogue_index >= second_list.Num()) {
			UGameplayStatics::OpenLevel(GetWorld(), FName(NextLevelName));
			
			return;
		}
		widget->homeless_negative->SetText(FText::FromString(FString::Printf(TEXT("%s"), *second_list[second_dialogue_index]->line_dialogue)));
		second_dialogue_index++;

	}



	if (hited && result.GetActor()->ActorHasTag(FName("oldman"))) {//처음 할아버지와의 재회이후 
		
		auto animinstance = Cast<Uplayer_animinstance>(GetMesh()->GetAnimInstance());
		if (animinstance) {
			animinstance->vertical = 0;
			animinstance->horizon = 0;
		}


		if (first_dialogue_index >= first_list.Num()) {

			widget->interaction_dialogue->SetText(FText::FromString(FString::Printf(TEXT(""))));
			is_dialogue = false;
			
			AAIController* AI_C = UAIBlueprintHelperLibrary::GetAIController(result.GetActor());
			auto homeless_ai = Cast<AHomeless_Ai>(AI_C);
			homeless_ai->homeless_move();


			return;
		}
		
		
		UE_LOG(LogTemp, Warning, TEXT("dialogue_start"));
		is_dialogue = true;
		widget->interaction_dialogue->SetText(FText::FromString(FString::Printf(TEXT("%s"), *first_list[first_dialogue_index]->line_dialogue)));
		first_dialogue_index++;
	}


}

void APlayerable_char::check_bone()
{
	if (num_skeleton == havetobone) {

		auto widget = Cast<UPlayer_widget>(first_ui);
		widget->interaction_dialogue->SetText(FText::FromString(FString::Printf(TEXT("return to lighthouse"))));
		is_quest_complete = true;
	}


}

void APlayerable_char::check_flash()
{
	is_flash = !is_flash;

	if (is_flash==true) {
		UE_LOG(LogTemp, Warning, TEXT("flash on"));
		UGameplayStatics::PlaySound2D(GetWorld(), sound_flash);
		spot_light->SetIntensity(5000.f);
	}
	else if (is_flash == false) {
		UE_LOG(LogTemp, Warning, TEXT("flash off"));
		UGameplayStatics::PlaySound2D(GetWorld(), sound_flash);
		spot_light->SetIntensity(0.f);
	}

}

// Called to bind functionality to input
void APlayerable_char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerable_char::FowardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerable_char::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &APlayerable_char::Yaw);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerable_char::Pitch);
	
	//action
	PlayerInputComponent->BindAction(TEXT("RUN"), IE_Pressed,this, &APlayerable_char::Sprint);
	PlayerInputComponent->BindAction(TEXT("RUN"), IE_Released, this, &APlayerable_char::Stop_Sprint);
	PlayerInputComponent->BindAction(TEXT("HammerAttack"), IE_Pressed, this, &APlayerable_char::Hammer_Attack);
	//PlayerInputComponent->BindAction(TEXT("Bandage"), IE_Pressed, this, &APlayerable_char::Bandage);
	//PlayerInputComponent->BindAction(TEXT("Drink"), IE_Pressed, this, &APlayerable_char::Drink);
	//PlayerInputComponent->BindAction(TEXT("Syringe"), IE_Pressed, this, &APlayerable_char::Syringe);
	PlayerInputComponent->BindAction(TEXT("Lookingfor"), IE_Pressed, this, &APlayerable_char::lookingfor);
	PlayerInputComponent->BindAction(TEXT("Take"), IE_Pressed, this, &APlayerable_char::take);
	PlayerInputComponent->BindAction(TEXT("Submenu"), IE_Pressed, this, &APlayerable_char::change_menu);
	PlayerInputComponent->BindAction(TEXT("dialogue"), IE_Pressed, this, &APlayerable_char::check_dialogue);
	PlayerInputComponent->BindAction(TEXT("flash"), IE_Pressed, this, &APlayerable_char::check_flash);
}

