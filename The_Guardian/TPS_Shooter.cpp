// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_Shooter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Soldier_SK_Container.h"
#include "Soldier_anim.h"
#include "Engine/DamageEvents.h"
#include "AR_01.h"
#include "AR_03.h"
#include "My_Default_gun.h"
// Sets default values
ATPS_Shooter::ATPS_Shooter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_SOLDIER(TEXT("/Script/Engine.SkeletalMesh'/Game/Customized_Soldier/Meshes/Mesh_UE4/Full_Skeleton/SK_Body_1.SK_Body_1'"));
	static ConstructorHelpers::FClassFinder<AAR_01>bp_ar_01(TEXT("/Script/Engine.Blueprint'/Game/Player_soldier/Gun/BP_AR_01.BP_AR_01_C'"));
	static ConstructorHelpers::FClassFinder<AAR_03>bp_ar_03(TEXT("/Script/Engine.Blueprint'/Game/Player_soldier/Gun/BP_AR_03.BP_AR_03_C'"));
	
	ar_01_socket = FName(TEXT("socket_ar_01"));
	ar_03_socket = FName(TEXT("socket_ar_03"));

	if (bp_ar_01.Succeeded()) {
		AR_01 = bp_ar_01.Class;
	}
	if (bp_ar_03.Succeeded()) {
		AR_03 = bp_ar_03.Class;
	}

	if (SK_SOLDIER.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_SOLDIER.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 100.0f;
	CameraBoom->SocketOffset = FVector(0.f,50.f,0.f);
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	soldier_container = CreateDefaultSubobject<USoldier_SK_Container>(TEXT("Soldier_container"));
	
	soldier_test_line_length = 10000;
	hp = 100.f;
	//soldier_anim = Cast<USoldier_anim>(GetMesh()->GetAnimInstance());

	//hand_weapon = CreateDefaultSubobject<AAR_01>(TEXT("WEAPON"));
	//hand_weapon = GetWorld()->SpawnActor<AAR_01>(GetMesh()->GetSocketLocation(ar_01_socket), GetMesh()->GetSocketRotation(ar_01_socket));


	//soldier_weapon_max_ammo = hand_weapon->max_ammo;


	//hand_weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("HAND_WEAPON"));
	//hand_weapon->SetupAttachment(GetMesh(), ar_01_socket);
	//hand_weapon->SetChildActorClass(AR_01);
	// 
	// 
	//hand_weapon->CreateChildActor();
	

}

void ATPS_Shooter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		soldier_vertical = MovementVector.Y;
		
		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		
		AddMovementInput(RightDirection, MovementVector.X);
	}


}

void ATPS_Shooter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		soldier_pitch = LookAxisVector.Y;
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}



}

void ATPS_Shooter::RunStart(const FInputActionValue& Value)
{
	soldier_run = Value.Get<bool>();
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	//UE_LOG(LogTemp, Log, TEXT("Character is running : %s"), soldier_run ? TEXT("true") : TEXT("false"));
}

void ATPS_Shooter::RunEnd(const FInputActionValue& Value)
{
	soldier_run = Value.Get<bool>();
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//UE_LOG(LogTemp, Log, TEXT("Character is running : %s"), soldier_run ? TEXT("true") : TEXT("false"));
}

void ATPS_Shooter::Play_reload(const FInputActionValue& Value)
{
	/*if (soldier_anim == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("static soldier anim is not exist"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("static soldier anim is exist"));
	}*/
	
	/*if (hand_weapon==nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("weapon pointer is not exist"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("weapon pointer is  exist"));
	}*/
	//auto weapon = Cast<AAR_01>(hand_weapon->GetChildActor());

	/*if (weapon) {
		UE_LOG(LogTemp, Warning, TEXT("aar_01 is  exist"));
	}*/
	//auto animinstance = Cast<USoldier_anim>(GetMesh()->GetAnimInstance());
	if (soldier_anim) {

		if (soldier_weapon_current_ammo > 0 && soldier_weapon_current_ammo < soldier_weapon_max_ammo) {
			soldier_anim->Reload_Montage();
			hand_weapon_obj->Reload();
		}

		else if (soldier_weapon_current_ammo==0) {
			soldier_anim->Reload_Empty_Montage();
			hand_weapon_obj->Reload();
		}
		
		
	}

}

void ATPS_Shooter::Weapon_Fire_Start(const FInputActionValue& Value)
{

	switch (current_shoot_type)
	{

		case EShootType::E_SINGLE:
			Regular_weapon_fire();
			break;

		case EShootType::E_AUTO:

			GetWorld()->GetTimerManager().SetTimer(myTimerHandle, this, &ATPS_Shooter::Regular_weapon_fire, soldier_weapon_interval, true);
			break;
	}
	

}

void ATPS_Shooter::Weapon_Fire_Stop(const FInputActionValue& Value)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(myTimerHandle)) {
		GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
	}
}

void ATPS_Shooter::Regular_weapon_fire()
{
	if (soldier_anim && soldier_weapon_current_ammo>0 && soldier_readytofire) {
	

		soldier_anim->Fire();
		hand_weapon_obj->Fire(Caculate_target_point());
		soldier_weapon_current_ammo--;
		/*UE_LOG(LogTemp, Warning, TEXT("weapon single fire activate"));
		UE_LOG(LogTemp, Warning, TEXT("current ammo : %d"),soldier_weapon_current_ammo);*/
	}
}

void ATPS_Shooter::Change_Fire_mode(const FInputActionValue& Value)
{
	if (current_shoot_type == EShootType::E_SINGLE) {
		current_shoot_type = EShootType::E_AUTO;
		UE_LOG(LogTemp, Warning, TEXT("change to auto"));
	}
	else {
		current_shoot_type = EShootType::E_SINGLE;
		UE_LOG(LogTemp, Warning, TEXT("change to single"));
	}
}

FVector ATPS_Shooter::Caculate_target_point()
{
	FVector camLocation;
	FRotator camRotation;

	soldier_controller->PlayerCameraManager->GetCameraViewPoint(camLocation, camRotation);

	FVector camForward = FRotationMatrix(camRotation).GetUnitAxis(EAxis::X);


	FVector endLocation;
	endLocation = camLocation + camForward * soldier_test_line_length;

	FHitResult Hit;
	bool isColl = GetWorld()->LineTraceSingleByChannel(Hit, camLocation, endLocation, ECC_GameTraceChannel2);
	DrawDebugLine(GetWorld(), camLocation, endLocation, FColor::Green, false,5.0f);
	
	
	if (isColl) // 충돌이 일어났음
	{
		return Hit.ImpactPoint;
	}
	return Hit.TraceEnd;
}



//void ATPS_Shooter::Fire(const FInputActionValue& Value)
//{
//
//}
//
//void ATPS_Shooter::Fire_Stop(const FInputActionValue& Value)
//{
//
//}
//
//void ATPS_Shooter::ReadyToFire(const FInputActionValue& Value)
//{
//
//}
//
//void ATPS_Shooter::Reload(const FInputActionValue& Value)
//{
//
//
//}



void ATPS_Shooter::ChangeAimMode(const FInputActionValue& Value)
{
	soldier_readytofire = !soldier_readytofire;
}

void ATPS_Shooter::reset_soldier_ammo()
{

	soldier_weapon_current_ammo = hand_weapon_obj->max_ammo;
	hand_weapon_obj->reset_gun_ammo();
}

// Called when the game starts or when spawned
void ATPS_Shooter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	

	/*if (hand_weapon_obj) {
		UE_LOG(LogTemp, Warning, TEXT("weapon in player hand is activeate"));
	}*/

	soldier_controller = Cast<APlayerController>(Controller);
	soldier_controller->PlayerCameraManager->ViewPitchMin = -40.f;
	soldier_controller->PlayerCameraManager->ViewPitchMax = 70.f;

	soldier_weapon_max_ammo = hand_weapon_obj->max_ammo;
	soldier_weapon_current_ammo = hand_weapon_obj->current_ammo;
	soldier_weapon_interval = hand_weapon_obj->launch_interval;
}

void ATPS_Shooter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	hand_weapon = nullptr;
	hand_weapon = NewObject<UChildActorComponent>(this);
	hand_weapon->SetupAttachment(GetMesh(), ar_01_socket);
	hand_weapon->RegisterComponent();
	//hand_weapon->SetupAttachment(GetMesh(), ar_01_socket);
	hand_weapon->SetChildActorClass(AR_01);
	

	soldier_anim= Cast<USoldier_anim>(GetMesh()->GetAnimInstance());
	hand_weapon_obj = Cast<AAR_01>(hand_weapon->GetChildActor());

	
	
}

// Called every frame
void ATPS_Shooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ATPS_Shooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);//점프시작
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);//점프중단

		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPS_Shooter::Look);//주변둘러보기
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPS_Shooter::Move);//움직임

		Input->BindAction(RunAction, ETriggerEvent::Triggered, this, &ATPS_Shooter::RunStart);//달리기 시작
		Input->BindAction(RunAction, ETriggerEvent::Completed, this, &ATPS_Shooter::RunEnd);//달리기 중단

		Input->BindAction(ReadyToFire, ETriggerEvent::Triggered, this, &ATPS_Shooter::ChangeAimMode);//에임모드 변경

		Input->BindAction(Reload, ETriggerEvent::Triggered, this, &ATPS_Shooter::Play_reload);//재장전

		Input->BindAction(Fire, ETriggerEvent::Started, this, & ATPS_Shooter::Weapon_Fire_Start);//무기 발사
		Input->BindAction(Fire, ETriggerEvent::Completed, this, &ATPS_Shooter::Weapon_Fire_Stop);//무기 발사 중단
		Input->BindAction(Change_shoot_mode, ETriggerEvent::Triggered, this, &ATPS_Shooter::Change_Fire_mode);//발사 모드 변경
	}


}

float ATPS_Shooter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("rocket player hited"));
		hp -= DamageAmount;

	}


	return Damage;
}

